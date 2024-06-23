#ifndef GENERIC_SETTING_H
#define GENERIC_SETTING_H

#include <QObject>
#include <QVariant>
#include "vrsettings.h"

class generic_setting : public QObject
{
    Q_OBJECT
public:
    explicit generic_setting(QObject *parent = nullptr);

    QString user_facing_name;
    QString setting_name;

signals:
    void changeSettingMemory(QString key, QVariant value);

public slots:
    virtual void updateSetting(VRSettings * vrsettings) = 0;

signals:
};



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
