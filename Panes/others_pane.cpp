#include "others_pane.h"
#include "ui_others_pane.h"
#include <QDebug>
#include <QLabel>

others_pane::others_pane(QWidget *parent, VRSettings * vrsettings)
    : generic_pane(parent)
    , ui(new Ui::others_pane)
{
    ui->setupUi(this);

    this->vrsettings = vrsettings;

    auto_settings = {
        new bool_setting(nullptr, "Enable Trackers", "Trackers:EnableTrackers", false),
        new number_setting(nullptr, "Tracker Mode", "Trackers:TrackerMode", 0),
        new bool_setting(nullptr, "Enable Drift Correction", "Experimental:EnableDriftCorrection", false),
        new number_setting(nullptr, "Lower Velocity Treshold", "Experimental:LowerVelocityTreshold", 2.0),
        new number_setting(nullptr, "Upper Velocity Treshold", "Experimental:UpperVelocityTreshold", 5.0),
        new number_setting(nullptr, "Measurement Uncertainty", "Experimental:Measurement_Uncertainty", 5.0),
        new number_setting(nullptr, "Estimation Uncertainty", "Experimental:Estimation_Uncertainty", 1.25),
        new number_setting(nullptr, "HMD Process Noise", "Experimental:HMD_Process_Noise", 0.0),
        new number_setting(nullptr, "Controller Process Noise", "Experimental:Controller_Process_Noise", 2.0),
    };


    int i = 0;
    for (auto setting : auto_settings){
        QLabel * tempQLabel = new QLabel();
        tempQLabel->setText(setting->user_facing_name);
        ui->gridLayout_auto->addWidget(tempQLabel, i, 0);
        connect(this, &others_pane::updateOtherSettings, setting, &generic_setting::updateSetting);
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

others_pane::~others_pane()
{
    delete ui;
}

void others_pane::enable(){
    qDebug() << "Enable others_pane";
}

void others_pane::disable(){
    qDebug() << "Disable others_pane";
}

void others_pane::updateSettings(VRSettings * vrsettings){
    emit updateOtherSettings(vrsettings);
}
