#include "hmd_pane.h"
#include "ui_hmd_pane.h"

#include <QSerialPortInfo>
#include <QSerialPort>

#include "include_ext/hidapi.h"

#include <QThread>
#include <QString>
#include <QDebug>
#include <algorithm>


class Worker : public QObject
{
    //Q_OBJECT
public:
    Worker(){}
    ~Worker(){}
public slots:
    void doWork() {
        auto handle = hid_enumerate(0,0);
        auto orig_handle = handle;

        while (handle != NULL){
            QString manufacturer = QString::fromWCharArray(handle->manufacturer_string);
            QString product =  QString::fromWCharArray(handle->product_string);
            QString serial_no = QString::fromWCharArray(handle->serial_number);
            qDebug() << "PID: " << handle->product_id << "VID: " << handle->vendor_id << " Product: " << product << "By: " << manufacturer <<" Serial: " << serial_no;
            handle = handle->next;
        }
        hid_free_enumeration(orig_handle);

        auto picoHandle = hid_enumerate(9114, 51966);

        if(!picoHandle) return;

        hid_device * pico = hid_open(9114, 51966, picoHandle->serial_number);
        hid_free_enumeration(picoHandle);
        if(!pico){
            qDebug() << "Failed hid open";
        } else {
            qDebug() << "Succ";
            for (;;){
                uint8_t packet_buffer[64];

                int res = hid_read(pico, packet_buffer, 66);
                if(res>0 && packet_buffer[0] == 2){
                    qDebug() << "Result: " << res;
                    //qDebug()  << packet_buffer[0] << packet_buffer[1] << packet_buffer[2] << packet_buffer[3] << packet_buffer[4] << packet_buffer[5] << packet_buffer[6];
                    qDebug()  << packet_buffer[17] << packet_buffer[18] << packet_buffer[19] << packet_buffer[20] << packet_buffer[21] << packet_buffer[22] << packet_buffer[23];
                }
            }
        }
    }
};


hmd_pane::hmd_pane(QWidget *parent)
    : generic_pane(parent)
    , ui(new Ui::hmd_pane)
{
    ui->setupUi(this);
    reload_serial();
    reload_hid();
    QThread * workerThread = new QThread();
    Worker * worker = new Worker;
    worker->moveToThread(workerThread);
    connect(workerThread, &QThread::started, worker, &Worker::doWork);
    connect(ui->refreshHID, &QPushButton::clicked, this, &hmd_pane::reload_hid);
    connect(ui->refreshSerial, &QPushButton::clicked, this, &hmd_pane::reload_serial);
    workerThread->start();
}

hmd_pane::~hmd_pane()
{
    delete ui;
}

void hmd_pane::enable(){
    qDebug() << "enable hmd pane";
}
void hmd_pane::disable(){
    qDebug() << "disable hmd pane";
}


void hmd_pane::on_transportBox_currentIndexChanged(int index)
{
    switch(index){
    case 0: // HID selected
        ui->COM_Box->setDisabled(true);
        ui->lineEdit_COM->setDisabled(true);
        ui->HID_Box->setDisabled(false);
        ui->lineEdit_PID->setDisabled(false);
        ui->lineEdit_VID->setDisabled(false);
        break;
    case 1: // Serial selected
        ui->COM_Box->setDisabled(false);
        ui->lineEdit_COM->setDisabled(false);
        ui->HID_Box->setDisabled(true);
        ui->lineEdit_PID->setDisabled(true);
        ui->lineEdit_VID->setDisabled(true);
        break;
    }
}


void hmd_pane::on_lineEdit_COM_textEdited(const QString &arg1)
{
    ui->COM_Box->setCurrentIndex(0);
}

void hmd_pane::reload_serial(){
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
        ui->COM_Box->addItem(device->user_presentable_name);
        serial_devices.push_back(device);
    }
}

void hmd_pane::on_COM_Box_currentIndexChanged(int index)
{
    if(index>0){
        ui->lineEdit_COM->setText(serial_devices[index-1]->path);
    }
}


void hmd_pane::on_lineEdit_VID_textEdited(const QString &arg1)
{
    ui->HID_Box->setCurrentIndex(0);
}
void hmd_pane::on_lineEdit_PID_textEdited(const QString &arg1)
{
    ui->HID_Box->setCurrentIndex(0);
}

bool HID_device::operator==(const HID_device &other){
    if (this->PID != other.PID) return false;
    if (this->VID != other.VID) return false;
    if (this->SerialNo != other.SerialNo) return false;
    return true;
}

void hmd_pane::reload_hid(){
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


void hmd_pane::on_HID_Box_currentIndexChanged(int index)
{
    if (index > 0){
        ui->lineEdit_PID->setText(hid_devices[index-1]->PID);
        ui->lineEdit_VID->setText(hid_devices[index-1]->VID);
    }
}

