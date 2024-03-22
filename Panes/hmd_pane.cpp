#include "hmd_pane.h"
#include "ui_hmd_pane.h"

hmd_pane::hmd_pane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hmd_pane)
{
    ui->setupUi(this);
}

hmd_pane::~hmd_pane()
{
    delete ui;
}
