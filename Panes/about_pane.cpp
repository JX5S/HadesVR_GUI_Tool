#include "about_pane.h"
#include "ui_about_pane.h"

about_pane::about_pane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::about_pane)
{
    ui->setupUi(this);
}

about_pane::~about_pane()
{
    delete ui;
}
