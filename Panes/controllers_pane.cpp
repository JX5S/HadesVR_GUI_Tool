#include "controllers_pane.h"
#include "ui_controllers_pane.h"

controllers_pane::controllers_pane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::controllers_pane)
{
    ui->setupUi(this);
}

controllers_pane::~controllers_pane()
{
    delete ui;
}
