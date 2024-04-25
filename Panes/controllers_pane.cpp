#include "controllers_pane.h"
#include "ui_controllers_pane.h"

#include <QQuickItem>
#include <QColor>
#include <QDebug>

controllers_pane::controllers_pane(QWidget *parent)
    : generic_pane(parent)
    , ui(new Ui::controllers_pane)
{
    ui->setupUi(this);
//    ui->quickWidget->setClearColor(Qt::transparent);
}

controllers_pane::~controllers_pane()
{
    delete ui;
}

void controllers_pane::enable(){
    qDebug() << "enable controllers pane";
}
void controllers_pane::disable(){
    qDebug() << "disable controllers pane";
}
