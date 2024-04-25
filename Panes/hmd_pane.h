#ifndef HMD_PANE_H
#define HMD_PANE_H

#include <QWidget>
#include <QSerialPortInfo>

#include "generic_pane.h"

namespace Ui {
class hmd_pane;
}

struct Serial_device{
    QString user_presentable_name = "";
    QString path = "";
};

struct HID_device{
    QString user_presentable_name = "";
    QString PID = "";
    QString VID = "";
    QString SerialNo = "";

    bool operator==(const HID_device &other);
};

class hmd_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit hmd_pane(QWidget *parent = nullptr);
    ~hmd_pane();
    void enable();
    void disable();

private slots:
    void on_COM_Box_currentIndexChanged(int index);

    void on_transportBox_currentIndexChanged(int index);

    void on_lineEdit_COM_textEdited(const QString &arg1);

    void on_lineEdit_VID_textEdited(const QString &arg1);

    void on_lineEdit_PID_textEdited(const QString &arg1);

    void on_HID_Box_currentIndexChanged(int index);

private:
    Ui::hmd_pane *ui;
    QList<Serial_device *> serial_devices;
    QList<HID_device *> hid_devices;
    void reload_serial();
    void reload_hid();
};

#endif // HMD_PANE_H
