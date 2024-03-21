#include "driver_pane.h"
#include "ui_driver_pane.h"

#include <QDesktopServices>
#include <QSettings>
#include <QDebug>
#include <QString>
#include <QFile>

Driver_pane::Driver_pane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Driver_pane)
{
    ui->setupUi(this);

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
        }
    }

    // Steam/SteamVR installation line
    if (!isSteamInstalled){
        ui->label_status_steamvr->setText("Steam is not installed");
        ui->button_steamvr->setText("Install Steam");
        ui->button_steamvr->setDisabled(false);
    } else if (!isSteamVRInstalled){
        ui->label_status_steamvr->setText("SteamVR is not installed");
        ui->button_steamvr->setText("Install SteamVR");
        ui->button_steamvr->setDisabled(false);
    } else {
        ui->label_status_steamvr->setText("SteamVR is installed");
        ui->button_steamvr->setText("Install SteamVR");
        ui->button_steamvr->setDisabled(true);
    }

    // HadesVR Driver installation line
    if (isSteamInstalled){
        ui->button_steamvr_driver->setDisabled(false);
    }


}

Driver_pane::~Driver_pane()
{
    delete ui;
}

void Driver_pane::on_button_steamvr_clicked()
{
    if (!isSteamInstalled){
        QDesktopServices::openUrl(QUrl("https://store.steampowered.com/about/"));
    } else if (!isSteamVRInstalled){
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

