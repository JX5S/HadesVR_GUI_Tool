#ifndef HMD_PANE_H
#define HMD_PANE_H

#include <QWidget>
#include <QSerialPortInfo>

#include "generic_pane.h"


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

namespace Ui {
class hmd_pane;
}

class hmd_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit hmd_pane(QWidget *parent = nullptr);
    ~hmd_pane();
    void enable();
    void disable();
    void updateSettings(VRSettings * vrsettings);

public slots:

private slots:


private:
    Ui::hmd_pane *ui;
};

#endif // HMD_PANE_H
