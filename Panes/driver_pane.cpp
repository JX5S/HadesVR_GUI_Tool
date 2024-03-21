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
    if (steamExe != "" && QFile::exists(steamExe)){
        isSteamInstalled = true;
    }



    if (!isSteamInstalled){
        ui->label_status_steamvr->setText("Steam is not installed");
        ui->button_steamvr->setText("Install Steam");
        ui->button_steamvr->setDisabled(false);
    } else if (!isSteamVRInstalled){
        ui->button_steamvr->setText("Install SteamVR");
        ui->button_steamvr->setDisabled(false);
    } else {
        ui->button_steamvr->setText("Install SteamVR");
        ui->button_steamvr->setDisabled(true);
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
