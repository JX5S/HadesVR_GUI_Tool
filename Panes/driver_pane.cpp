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

Driver_pane::Driver_pane(QWidget *parent)
    : generic_pane(parent)
    , ui(new Ui::Driver_pane)
{
    ui->setupUi(this);
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

