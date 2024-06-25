#ifndef GENERIC_SETTING_H
#define GENERIC_SETTING_H

#include <QObject>
#include <QVariant>
#include "vrsettings.h"

// Used for quick filling of various settings. Others are done by hand in the .ui files

class generic_setting : public QObject
{
    Q_OBJECT
public:
    explicit generic_setting(QObject *parent = nullptr);

    QString user_facing_name;
    QString setting_name;

signals:
    // main signal that connects various UI elements to the single vrsettings instance
    void changeSettingMemory(QString key, QVariant value);

public slots:
    // a general signal "settings have changed; reload" - ran on start or when "reload from disk" clicked
    virtual void updateSetting(VRSettings * vrsettings) = 0;

signals:
};


// Setting that includes a name and is a boolean value. Creates a checkbox

#include <QCheckBox>

class bool_setting : public generic_setting
{
    Q_OBJECT
public:
    explicit bool_setting(QWidget *parent = nullptr, QString user_facing_name = "", QString setting_name = "", bool default_val = false);
    ~bool_setting(){}
    QCheckBox * bool_checkBox;

public slots:
    void setting_changed(bool arg);
    void updateSetting(VRSettings * vrsettings);
};


// Setting that includes a name and a number value. Creates a lineedit

#include <QLineEdit>

class number_setting : public generic_setting
{
    Q_OBJECT
public:
    explicit number_setting(QWidget *parent = nullptr, QString user_facing_name = "", QString setting_name = "", float default_val = 0.);
    ~number_setting(){}
    QLineEdit * number_lineEdit;

public slots:
    void setting_changed(QString arg);
    void updateSetting(VRSettings * vrsettings);
};


#endif // GENERIC_SETTING_H
