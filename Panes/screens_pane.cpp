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
    QVBoxLayout * radky = new QVBoxLayout(parent);
    bool color = 0;
    for(int i = 1; i <= 8; i++){
        QHBoxLayout * radek = new QHBoxLayout(parent);
        for(char c = 'A'; c <= 'H'; c++){
            QString label = QString("%1%2").arg(i).arg(c);
            QPushButton * tButton = new QPushButton(label);
            tButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            tButton->setMinimumSize(30, 30);
            radek->addWidget(tButton);
            color = !color;
        }
        radky->addLayout(radek);
    }
    this->setLayout(radky);
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
