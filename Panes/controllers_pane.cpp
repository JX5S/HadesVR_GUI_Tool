#include "controllers_pane.h"
#include "ui_controllers_pane.h"
#include "QQuickItem"
#include "QColor"

controllers_pane::controllers_pane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::controllers_pane)
{
    ui->setupUi(this);
//    ui->quickWidget->setClearColor(Qt::transparent);
}

controllers_pane::~controllers_pane()
{
    delete ui;
}
