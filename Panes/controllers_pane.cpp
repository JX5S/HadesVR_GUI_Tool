#include "controllers_pane.h"
#include "ui_controllers_pane.h"

#include <QQuickItem>
#include <QColor>
#include <QDebug>
#include <QSpacerItem>

controllers_pane::controllers_pane(QWidget *parent, VRSettings * vrsettings)
    : generic_pane(parent)
    , ui(new Ui::controllers_pane)
{
    ui->setupUi(this);

    this->vrsettings = vrsettings;

    auto_settings = {
        new number_setting(nullptr, "Camera Kalman Measurement Uncertainty:", "Controllers:Camera_Kalman_Measurement_Uncertainty", 2),
        new number_setting(nullptr, "Camera Kalman Estimation Uncertainty", "Controllers:Camera_Kalman_Estimation_Uncertainty", 1.5),
        new number_setting(nullptr, "Camera Kalman Process Noise", "Controllers:Camera_Kalman_Process_Noise", 2.25),
        new number_setting(nullptr, "IMU Kalman Measurement Uncertainty", "Controllers:IMU_Kalman_Measurement_Uncertainty", 2),
        new number_setting(nullptr, "IMU Kalman Estimation Uncertainty", "Controllers:IMU_Kalman_Estimation_Uncertainty", 5),
        new number_setting(nullptr, "IMU Kalman Process Noise", "Controllers:IMU_Kalman_Process_Noise", 80),
        new number_setting(nullptr, "CTRL Right Yaw Offset", "Controllers:CTRLRightYawOffset", 0),
        new number_setting(nullptr, "CTRL Right Pitch Offset", "Controllers:CTRLRightPitchOffset", 32),
        new number_setting(nullptr, "CTRL Right Roll Offset", "Controllers:CTRLRightRollOffset", 0),
        new number_setting(nullptr, "CTRL Right X Offset", "Controllers:CTRLRightXOffset", 0.05),
        new number_setting(nullptr, "CTRL Right Y Offset", "Controllers:CTRLRightYOffset", -0.035),
        new number_setting(nullptr, "CTRL Right Z Offset", "Controllers:CTRLRightZOffset", 0.025),
        new number_setting(nullptr, "CTRL Left Yaw Offset", "Controllers:CTRLLeftYawOffset", 0),
        new number_setting(nullptr, "CTRL Left Pitch Offset", "Controllers:CTRLLeftPitchOffset", 32),
        new number_setting(nullptr, "CTRL Left Roll Offset", "Controllers:CTRLLeftRollOffset", 0),
        new number_setting(nullptr, "CTRL Left X Offset", "Controllers:CTRLLeftXOffset", -0.05),
        new number_setting(nullptr, "CTRL Left Y Offset", "Controllers:CTRLLeftYOffset", -0.035),
        new number_setting(nullptr, "CTRL Left Z Offset", "Controllers:CTRLLeftZOffset", 0.025),
    };


    int i = 0;
    for (auto setting : auto_settings){
        QLabel * tempQLabel = new QLabel();
        tempQLabel->setText(setting->user_facing_name);
        ui->gridLayout_auto->addWidget(tempQLabel, i, 0);
        connect(this, &controllers_pane::updateControllerSettings, setting, &generic_setting::updateSetting);
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


//    ui->quickWidget->setClearColor(Qt::transparent);
}

controllers_pane::~controllers_pane()
{
    delete ui;
}

void controllers_pane::enable(){
    qDebug() << "enable controllers pane";
}
void controllers_pane::disable(){
    qDebug() << "disable controllers pane";
}

void controllers_pane::updateSettings(VRSettings * vrsettings)
{
    ui->checkBoxEnableControllers->setChecked(vrsettings->settingsMap["Controllers:EnableControllers"].toBool());
    ui->checkBoxAccelerometers->setChecked(vrsettings->settingsMap["Controllers:UseAccelerometers"].toBool());
    ui->comboBoxControllerType->setCurrentIndex(vrsettings->settingsMap["Controllers:ControllerMode"].toInt());
    emit updateControllerSettings(vrsettings);
}

void controllers_pane::on_checkBoxEnableControllers_toggled(bool checked)
{
    emit changeSettingMemory("Controllers:EnableControllers", checked);
}

void controllers_pane::on_comboBoxControllerType_currentIndexChanged(int index)
{
    emit changeSettingMemory("Controllers:ControllerMode", index);
}


void controllers_pane::on_checkBoxAccelerometers_toggled(bool checked)
{
    emit changeSettingMemory("Controllers:UseAccelerometers", checked);
}

