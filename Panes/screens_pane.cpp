#include "screens_pane.h"
#include "qscreen.h"
#include "ui_screens_pane.h"
#include "QLayout"
#include "qpushbutton"
#include "QString"
#include <QGuiApplication>


screens_pane::screens_pane(QWidget *parent)
    : generic_pane(parent)
    , ui(new Ui::screens_pane)
{
    ui->setupUi(this);
}

screens_pane::~screens_pane()
{
    delete ui;
}

void screens_pane::enable(){
    qDebug() << "enable screens pane";
    QList<QScreen *> screens = QApplication::screens();
    qDebug() << "=================================";
    for (QScreen * screen : screens){
        qDebug() << "FPS:" << screen->refreshRate();
        qDebug() << "Name:" << screen->name();
        qDebug() << "Manufacturer:" << screen->manufacturer();
        qDebug() << "Model:" << screen->model();
        qDebug() << "Size:" << screen->size();
        qDebug() << "Geometry:" << screen->geometry();
        qDebug() << "Ratio:" << screen->devicePixelRatio(); // This is so utterly brainless
        qDebug() << "=================================";
    }
}
void screens_pane::disable(){
    qDebug() << "disable screens pane";
}

void screens_pane::updateSettings(VRSettings * vrsettings){

}
