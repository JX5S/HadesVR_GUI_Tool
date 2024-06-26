#include "about_pane.h"
#include "ui_about_pane.h"
#include <QDebug>

about_pane::about_pane(QWidget *parent, VRSettings * vrsettings)
    : generic_pane(parent)
    , ui(new Ui::about_pane)
{
    ui->setupUi(this);
    this->vrsettings = vrsettings;
}

about_pane::~about_pane()
{
    delete ui;
}

void about_pane::enable(){
    qDebug() << "Enable about_pane";
}

void about_pane::disable(){
    qDebug() << "Disable about_pane";
}

void about_pane::updateSettings(VRSettings * vrsettings){

}
