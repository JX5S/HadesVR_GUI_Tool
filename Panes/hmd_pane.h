#ifndef HMD_PANE_H
#define HMD_PANE_H

#include <QWidget>
#include <QSerialPortInfo>

#include "generic_pane.h"
#include "generic_setting.h"


class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(){}
    ~Worker(){}
public slots:
    void doWork();
signals:
    void accX(int16_t accelX);
};


// =======================================


namespace Ui {
class hmd_pane;
}

class hmd_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit hmd_pane(QWidget *parent = nullptr, VRSettings * vrsettings = nullptr);
    ~hmd_pane();
    void enable();
    void disable();
    void updateSettings(VRSettings * vrsettings);

public slots:

signals:
    void updateHMDSettings(VRSettings * vrsettings);

private slots:


    void on_checkBoxEnableHMD_toggled(bool checked);

    void on_lineEditSerialNumber_textEdited(const QString &arg1);

    void on_lineEditModelNumber_textEdited(const QString &arg1);

private:
    Ui::hmd_pane *ui;
    VRSettings * vrsettings;
    QVector<generic_setting *> auto_settings;
};

#endif // HMD_PANE_H
