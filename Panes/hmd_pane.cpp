#include "hmd_pane.h"
#include "ui_hmd_pane.h"

#include <QSerialPortInfo>
#include <QSerialPort>

#include "include_ext/hidapi.h"

#include <QThread>
#include <QString>
#include <QDebug>
#include <algorithm>

hmd_pane::hmd_pane(QWidget *parent, VRSettings * vrsettings)
    : generic_pane(parent)
    , ui(new Ui::hmd_pane)
{
    ui->setupUi(this);

    this->vrsettings = vrsettings;


    auto_settings = {
        new number_setting(nullptr, "Min Filter Beta", "HMD:MinFilterBeta", 0.01),
        new number_setting(nullptr, "Max Filter Beta", "HMD:MaxFilterBeta", 0.35),
        new bool_setting(nullptr, "Use Accelerometers", "HMD:UseAccelerometers", true),
        new number_setting(nullptr, "Camera Kalman Measurement Uncertainty", "HMD:Camera_Kalman_Measurement_Uncertainty", 5),
        new number_setting(nullptr, "Camera Kalman Estimation Uncertainty", "HMD:Camera_Kalman_Estimation_Uncertainty", 1.5),
        new number_setting(nullptr, "Camera Kalman Process_Noise", "HMD:Camera_Kalman_Process_Noise", 10),
        new number_setting(nullptr, "IMU Kalman Measurement Uncertainty", "HMD:IMU_Kalman_Measurement_Uncertainty", 2),
        new number_setting(nullptr, "IMU Kalman Estimation Uncertainty", "HMD:IMU_Kalman_Estimation_Uncertainty", 5),
        new number_setting(nullptr, "IMU Kalman Process Noise", "HMD:IMU_Kalman_Process_Noise", 8),
        new number_setting(nullptr, "HMD Yaw Offset", "HMD:HMDYawOffset", 0),
        new number_setting(nullptr, "HMD Pitch Offset", "HMD:HMDPitchOffset", 0),
        new number_setting(nullptr, "HMD Roll Offset", "HMD:HMDRollOffset", 0),
        new number_setting(nullptr, "HMD X Offset", "HMD:HMDXOffset", 0),
        new number_setting(nullptr, "HMD Y Offset", "HMD:HMDYOffset", 0),
        new number_setting(nullptr, "HMD Z Offset", "HMD:HMDZOffset", 0),
    };


    int i = 0;
    for (auto setting : auto_settings){
        QLabel * tempQLabel = new QLabel();
        tempQLabel->setText(setting->user_facing_name);
        ui->gridLayout_auto->addWidget(tempQLabel, i, 0);
        connect(this, &hmd_pane::updateHMDSettings, setting, &generic_setting::updateSetting);
        connect(setting, &generic_setting::changeSettingMemory, vrsettings, &VRSettings::changeSetting);

        if (bool_setting * derived_bool_setting = dynamic_cast<bool_setting *>(setting)) {
            qDebug() << "Is bool setting.";
            ui->gridLayout_auto->addWidget(derived_bool_setting->bool_checkBox, i, 1);
        } else if (number_setting * derived_number_setting = dynamic_cast<number_setting *>(setting)) {
            qDebug() << "Isn't bool setting";
            ui->gridLayout_auto->addWidget(derived_number_setting->number_lineEdit, i, 1);
        }
        i++;
    }

    QSpacerItem * horizontalSpacer = new QSpacerItem(5, 5, QSizePolicy::Expanding);
    ui->gridLayout_auto->addItem(horizontalSpacer, 0, 2);

    ui->gridLayout_auto->setColumnMinimumWidth(0, 150);
    ui->gridLayout_auto->setColumnMinimumWidth(1, 150);
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

void hmd_pane::on_lineEditSerialNumber_textEdited(const QString &arg1)
{
    emit changeSettingMemory("HMD:serialNumber", arg1);
}


void hmd_pane::on_lineEditModelNumber_textEdited(const QString &arg1)
{
    emit changeSettingMemory("HMD:modelNumber", arg1);
}

void hmd_pane::on_checkBoxEnableHMD_toggled(bool checked)
{
    emit changeSettingMemory("HMD:EnableHMD", checked);
}

void hmd_pane::updateSettings(VRSettings * vrsettings){
    qDebug() << "It has been called upon hmd_pane";
    ui->lineEditModelNumber->setText(vrsettings->settingsMap["HMD:modelNumber"].toString());
    ui->lineEditSerialNumber->setText(vrsettings->settingsMap["HMD:serialNumber"].toString());
    ui->checkBoxEnableHMD->setChecked(vrsettings->settingsMap["HMD:EnableHMD"].toBool());
    emit updateHMDSettings(vrsettings);
}

