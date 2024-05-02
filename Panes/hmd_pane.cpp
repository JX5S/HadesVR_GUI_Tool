#include "hmd_pane.h"
#include "ui_hmd_pane.h"

#include <QSerialPortInfo>
#include <QSerialPort>

#include "include_ext/hidapi.h"

#include <QThread>
#include <QString>
#include <QDebug>
#include <algorithm>

void Worker::doWork() {
    auto handle = hid_enumerate(0,0);
    auto orig_handle = handle;

    while (handle != NULL){
        QString manufacturer = QString::fromWCharArray(handle->manufacturer_string);
        QString product =  QString::fromWCharArray(handle->product_string);
        QString serial_no = QString::fromWCharArray(handle->serial_number);
        qDebug() << "PID: " << handle->product_id << "VID: " << handle->vendor_id << " Product: " << product << "By: " << manufacturer <<" Serial: " << serial_no;
        handle = handle->next;
    }
    hid_free_enumeration(orig_handle);

    auto picoHandle = hid_enumerate(9114, 51966);

    if(!picoHandle) return;

    hid_device * pico = hid_open(9114, 51966, picoHandle->serial_number);
    hid_free_enumeration(picoHandle);
    if(!pico){
        qDebug() << "Failed hid open";
    } else {
        qDebug() << "Succ";
        for (;;){
            uint8_t packet_buffer[64];

            int res = hid_read(pico, packet_buffer, 66);
            if(res>0 && packet_buffer[0] == 3){
                int16_t accelX = packet_buffer[4] << 8 | packet_buffer[3];
                emit accX(accelX);
//                qDebug() << "ACCx: " << accelX;
            }
        }
    }
}

hmd_pane::hmd_pane(QWidget *parent)
    : generic_pane(parent)
    , ui(new Ui::hmd_pane)
{
    ui->setupUi(this);
    ui->quickWidget->setClearColor(palette().color(QPalette::Window));
    QThread * workerThread = new QThread();
    Worker * worker = new Worker;
    worker->moveToThread(workerThread);
    connect(workerThread, &QThread::started, worker, &Worker::doWork);
    workerThread->start();
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

void hmd_pane::updateSettings(VRSettings * vrsettings){

}






