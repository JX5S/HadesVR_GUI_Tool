#ifndef DRIVER_PANE_H
#define DRIVER_PANE_H

#include <QWidget>
#include <QDebug>
#include <QTimer>

#include "generic_pane.h"

namespace Ui {
class Driver_pane;
}

struct Serial_device{
    QString user_presentable_name = "";
    QString path = "";
    QString baudrate = "230400";
};

struct HID_device{
    QString user_presentable_name = "";
    QString PID = "";
    QString VID = "";
    QString SerialNo = "";

    bool operator==(const HID_device &other);
};

class Driver_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit Driver_pane(QWidget *parent = nullptr);
    ~Driver_pane();
    void enable();
    void disable();

private slots:
    void on_button_steamvr_clicked();
    void on_button_steamvr_driver_clicked();
    void on_button_hadesvr_clicked();
    void on_pushButton_clicked();
    void refresh();
    void on_SettingSelectPushbutton_clicked();
    void on_COM_Box_currentIndexChanged(int index);
    void on_transportBox_currentIndexChanged(int index);
    void on_lineEdit_COM_textEdited(const QString &arg1);
    void on_lineEdit_VID_textEdited(const QString &arg1);
    void on_lineEdit_PID_textEdited(const QString &arg1);
    void on_HID_Box_currentIndexChanged(int index);

    void reload_serial();
    void reload_hid();

private:
    Ui::Driver_pane *ui;
    bool isSteamInstalled = false;
    bool isSteamVRInstalled = false;
    bool isHadesVRInstalled = false;
    QString SteamVR_drivers_folder = "";
    QTimer timer;
    QList<Serial_device *> serial_devices;
    QList<HID_device *> hid_devices;
};

#endif // DRIVER_PANE_H
