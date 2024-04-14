#include "hmd_pane.h"
#include "ui_hmd_pane.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

hmd_pane::hmd_pane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hmd_pane)
{
    ui->setupUi(this);
    ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        QString name = port.portName();
        if (port.manufacturer() != ""){
            name += " (" + port.manufacturer() + ")";
        }
        ui->COM_Box->addItem(name);
    }
}

hmd_pane::~hmd_pane()
{
    delete ui;
}

void hmd_pane::on_COM_Box_currentIndexChanged(int index)
{
    if(index){
        ui->lineEdit_COM->setText(ports[index-1].portName());
    }
}

