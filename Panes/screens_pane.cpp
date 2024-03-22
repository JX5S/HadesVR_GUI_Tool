#include "screens_pane.h"
#include "ui_screens_pane.h"

screens_pane::screens_pane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::screens_pane)
{
    ui->setupUi(this);
}

screens_pane::~screens_pane()
{
    delete ui;
}
