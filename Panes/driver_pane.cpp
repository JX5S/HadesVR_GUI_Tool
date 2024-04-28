#include "driver_pane.h"
#include "ui_driver_pane.h"
#include "mainwindow.h"

#include <QDesktopServices>
#include <QSettings>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTimer>
#include <QFileDialog>
#include <QSerialPortInfo>

#include "include_ext/hidapi.h"

Driver_pane::Driver_pane(QWidget *parent)
    : generic_pane(parent)
    , ui(new Ui::Driver_pane)
{
    ui->setupUi(this);
    reload_serial();
    reload_hid();
    connect(ui->refreshHID, &QPushButton::clicked, this, &Driver_pane::reload_hid);
    connect(ui->refreshSerial, &QPushButton::clicked, this, &Driver_pane::reload_serial);
    refresh();
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(refresh()));
    this->enable();
}

Driver_pane::~Driver_pane()
{
    delete ui;
}

void Driver_pane::refresh()
{
    // SteamVR status section
    QSettings settings("HKEY_CURRENT_USER\\Software\\Valve\\Steam", QSettings::NativeFormat);
    QString steamExe = settings.value("SteamExe").toString();

    isSteamInstalled = false;
    isSteamVRInstalled = false;
    if (steamExe != "" && QFile::exists(steamExe)){
        isSteamInstalled = true;
        isSteamVRInstalled = settings.value("Apps/250820/Installed").toBool();
        SteamVR_drivers_folder = settings.value("SteamPath").toString() + "/steamapps/common/SteamVR/drivers";
        if (!QFile::exists(SteamVR_drivers_folder)){
            SteamVR_drivers_folder = "";
        }
        if (QFile::exists(SteamVR_drivers_folder + "/hadesvr/resources/settings/default.vrsettings")){
            ui->label_status_hadesvr->setText("HadesVR is probably installed");
            ui->label_status_hadesvr->setToolTip("Only default.vrsettings file is actually checked - but if that is in the correct place, the rest should be fine too");
            if (!isHadesVRInstalled){
                ui->settingsLineEdit->setText(SteamVR_drivers_folder + "/hadesvr/resources/settings/default.vrsettings");
            }
            isHadesVRInstalled = true;
        } else {
            ui->label_status_hadesvr->setText("HadesVR is not installed");
            ui->label_status_hadesvr->setToolTip("");
            if (isHadesVRInstalled){
                ui->settingsLineEdit->setText("");
            }
            isHadesVRInstalled = false;
        }
    }

    // Steam/SteamVR installation line
    if (!isSteamInstalled){
        ui->label_status_steamvr->setText("Steam is not installed");
        ui->button_steamvr->setText("Install Steam");
    } else if (!isSteamVRInstalled){
        ui->label_status_steamvr->setText("SteamVR is not installed");
        ui->button_steamvr->setText("Install SteamVR");
    } else {
        ui->label_status_steamvr->setText("SteamVR is installed");
        ui->button_steamvr->setText("Launch SteamVR");
    }

    // HadesVR Driver installation line
    if (isSteamVRInstalled){
        ui->button_steamvr_driver->setDisabled(false);
    } else {
        ui->button_steamvr_driver->setDisabled(true);
    }
}

void Driver_pane::on_button_steamvr_clicked()
{
    if (!isSteamInstalled){
        QDesktopServices::openUrl(QUrl("https://store.steampowered.com/about/"));
    } else {
        QDesktopServices::openUrl(QUrl("steam://run/250820"));
    }
}

void Driver_pane::on_button_steamvr_driver_clicked()
{
    if (SteamVR_drivers_folder != ""){
        QDesktopServices::openUrl(QUrl("file:///" + SteamVR_drivers_folder));
    }
}


void Driver_pane::on_button_hadesvr_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/HadesVR/HadesVR/releases"));
}


void Driver_pane::on_pushButton_clicked()
{
    refresh();
}

void Driver_pane::enable(){
    qDebug() << "enable driver pane";
    this->timer.start(1000);
}
void Driver_pane::disable(){
    qDebug() << "disable driver pane";
    this->timer.stop();
}


void Driver_pane::on_SettingSelectPushbutton_clicked()
{
    QString result = QFileDialog::getOpenFileName(this, tr("Select .vrsettings file"), SteamVR_drivers_folder, tr("VR settings file (*.vrsettings)"));
    if (result != ""){
        ui->settingsLineEdit->setText(result);
    }
}

void Driver_pane::on_lineEdit_COM_textEdited(const QString &arg1)
{
    ui->COM_Box->setCurrentIndex(0);
}

void Driver_pane::reload_serial(){
    QList<QSerialPortInfo> ports;
    qDeleteAll(serial_devices);
    serial_devices.clear();
    ui->COM_Box->clear();
    ui->COM_Box->addItem("Manual");
    ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        if(!port.hasProductIdentifier() && !port.hasVendorIdentifier()) continue; // For some reason, disconnected devices are still otherwise detected
        Serial_device * device = new Serial_device;
        device->user_presentable_name = port.portName();
        if (port.manufacturer() != ""){
            device->user_presentable_name += " (" + port.manufacturer() + ")";
        }
        device->path = port.portName();
        auto baudrates = port.standardBaudRates();
        int maxBaudrate = 9600;
        for(auto baudrate : baudrates){
            maxBaudrate = qMax(maxBaudrate, baudrate);
        }
        device->baudrate = QString::number(maxBaudrate);
        ui->COM_Box->addItem(device->user_presentable_name);
        serial_devices.push_back(device);
    }
}

void Driver_pane::on_COM_Box_currentIndexChanged(int index)
{
    if(index>0){
        ui->lineEdit_COM->setText(serial_devices[index-1]->path);
        ui->lineEdit_Baud->setText(serial_devices[index-1]->baudrate);
    }
}


void Driver_pane::on_lineEdit_VID_textEdited(const QString &arg1)
{
    ui->HID_Box->setCurrentIndex(0);
}
void Driver_pane::on_lineEdit_PID_textEdited(const QString &arg1)
{
    ui->HID_Box->setCurrentIndex(0);
}

bool HID_device::operator==(const HID_device &other){
    if (this->PID != other.PID) return false;
    if (this->VID != other.VID) return false;
    if (this->SerialNo != other.SerialNo) return false;
    return true;
}

void Driver_pane::reload_hid(){
    auto handle = hid_enumerate(0,0);
    qDeleteAll(hid_devices);
    hid_devices.clear();
    ui->HID_Box->clear();
    ui->HID_Box->addItem("Manual");
    while (handle != NULL){
        QString manufacturer = QString::fromWCharArray(handle->manufacturer_string);
        QString product =  QString::fromWCharArray(handle->product_string);
        QString PID = QString::number(handle->product_id);
        QString VID = QString::number(handle->vendor_id);
        QString serial_no = QString::fromWCharArray(handle->serial_number);

        HID_device * device = new HID_device;
        device->PID = PID;
        device->VID = VID;
        device->SerialNo = serial_no;
        device->user_presentable_name = product + " (" + manufacturer + ")";

        // checks for duplicated devices. This considers devices identical when their PIDs, VIDs and Serial numbers match. Uses overloaded == operator above
        if (std::find_if(hid_devices.begin(), hid_devices.end(), [&device](HID_device* other) { return (*other == *device);}) == hid_devices.end()){
            hid_devices.push_back(device);
            ui->HID_Box->addItem(device->user_presentable_name);
        } else {
            delete(device);
        }
        handle = handle->next;
    }
    hid_free_enumeration(handle);
}


void Driver_pane::on_HID_Box_currentIndexChanged(int index)
{
    if (index > 0){
        ui->lineEdit_PID->setText(hid_devices[index-1]->PID);
        ui->lineEdit_VID->setText(hid_devices[index-1]->VID);
    }
}

void Driver_pane::on_transportBox_currentIndexChanged(int index)
{
    // switch(index){
    // case 0: // HID selected
    //     ui->COM_Box->setDisabled(true);
    //     ui->lineEdit_COM->setDisabled(true);
    //     ui->HID_Box->setDisabled(false);
    //     ui->lineEdit_PID->setDisabled(false);
    //     ui->lineEdit_VID->setDisabled(false);
    //     break;
    // case 1: // Serial selected
    //     ui->COM_Box->setDisabled(false);
    //     ui->lineEdit_COM->setDisabled(false);
    //     ui->HID_Box->setDisabled(true);
    //     ui->lineEdit_PID->setDisabled(true);
    //     ui->lineEdit_VID->setDisabled(true);
    //     break;
    // }
}
