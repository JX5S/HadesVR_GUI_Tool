#include "generic_setting.h"

generic_setting::generic_setting(QObject *parent)
    : QObject{parent}
{}


// ===========================================


bool_setting::bool_setting(QWidget *parent, QString user_facing_name, QString setting_name, bool default_val)
{
    this->user_facing_name = user_facing_name;
    this->setting_name = setting_name;
    bool_checkBox = new QCheckBox();
    bool_checkBox->setText("");
    bool_checkBox->setChecked(default_val);
    connect(this->bool_checkBox, &QCheckBox::clicked, this, &bool_setting::setting_changed);
}

void bool_setting::setting_changed(bool arg)
{
    emit changeSettingMemory(this->setting_name, arg);
}

void bool_setting::updateSetting(VRSettings * vrsettings)
{
    this->bool_checkBox->setChecked(vrsettings->settingsMap[this->setting_name].toBool());
}


// ===========================================



number_setting::number_setting(QWidget *parent, QString user_facing_name, QString setting_name, float default_val)
{
    this->user_facing_name = user_facing_name;
    this->setting_name = setting_name;
    number_lineEdit = new QLineEdit();
    number_lineEdit->setText(QString::number(default_val));
    number_lineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(this->number_lineEdit, &QLineEdit::textEdited, this, &number_setting::setting_changed);
}

void number_setting::setting_changed(QString arg)
{
    emit changeSettingMemory(this->setting_name, arg.replace(",",".").toDouble()); // replace because I have ',' as decimal on my numpad, but QT believes in '.'
}

void number_setting::updateSetting(VRSettings * vrsettings)
{
    this->number_lineEdit->setText(QString::number(vrsettings->settingsMap[this->setting_name].toReal()));
}
