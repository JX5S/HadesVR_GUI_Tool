#include "others_pane.h"
#include "ui_others_pane.h"
#include <QDebug>

others_pane::others_pane(QWidget *parent, VRSettings * vrsettings)
    : generic_pane(parent)
    , ui(new Ui::others_pane)
{
    ui->setupUi(this);

    this->vrsettings = vrsettings;
}

others_pane::~others_pane()
{
    delete ui;
}

void others_pane::enable(){
    qDebug() << "Enable others_pane";
}

void others_pane::disable(){
    qDebug() << "Disable others_pane";
}

void others_pane::updateSettings(VRSettings * vrsettings){

}
