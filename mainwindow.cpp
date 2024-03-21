#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Panes/driver_pane.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CurrentContent = new Driver_pane(ui->splitter);
    CurrentContent->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
