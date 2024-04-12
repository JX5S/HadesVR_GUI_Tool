#include "controllers_pane.h"
#include "ui_controllers_pane.h"
#include "QQuickItem"

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

void controllers_pane::on_pushButton_clicked()
{
    auto obj = ui->quickWidget->rootObject();
    QMetaObject::invokeMethod(obj, "startAnimationCpp");
}

