#include "screens_pane.h"
#include "ui_screens_pane.h"
#include <QLayout>
#include <QPushButton>
#include <QString>
#include <QGuiApplication>
#include <QScreen>


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
    refresh();
}
void screens_pane::disable(){
    qDebug() << "disable screens pane";
}

void screens_pane::updateSettings(VRSettings * vrsettings){

}

void screens_pane::refresh(){
    int minX = 0, minY = 0, maxX = 0, maxY = 0;
    qDebug() << "enable screens pane";
    QList<QScreen *> screens = QApplication::screens();
    qDebug() << "=================================";
    for (QScreen * screen : screens){
        QRect geometry = screen->geometry();
        geometry.setSize(screen->devicePixelRatio() * geometry.size());
        minX = std::min(minX, geometry.left());
        minY = std::min(minY, geometry.top());
        maxX = std::max(maxX, geometry.right()+1);
        maxY = std::max(maxY, geometry.bottom()+1);
        qDebug() << "FPS:" << screen->refreshRate();
        qDebug() << "Name:" << screen->name();
        qDebug() << "Manufacturer:" << screen->manufacturer();
        qDebug() << "Model:" << screen->model();
        qDebug() << "Size:" << screen->size();
        // This is ridiculous. Resolution reported by Geometry() is scaled down by the scaling ratio and rounded. That means we can have rounding errors, which will cause SteamVR to fail, so a warning popup is needed
        qDebug() << "Geometry:" << geometry;
        qDebug() << "Ratio:" << screen->devicePixelRatio();
        qDebug() << "=================================";
    }
    qDebug() << "Screen count: " << screens.count();
    qDebug() << "MinX = " << minX;
    qDebug() << "MaxX = " << maxX;
    qDebug() << "MinY = " << minY;
    qDebug() << "MaxY = " << maxY;
    qDebug() << "=================================";

    QLayoutItem *child;
    while ((child = ui->buttonLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }

    for(int i = 0; i < screens.count(); i++){
        QPushButton * currBtn = new QPushButton();
        currBtn->setText(QString::number(i+1));
        ui->buttonLayout->addWidget(currBtn);
    }
}
