#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

#define driver_btn_id 0
#define hmd_btn_id 1
#define screens_btn_id 2
#define controller_btn_id 3
#define about_btn_id 4

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CurrentContent = new Driver_pane(ui->splitter);
    CurrentContent->show();
    QObject::connect(ui->paneButtonGroup, &QButtonGroup::idClicked, this, &MainWindow::on_pane_button_clicked);
    ui->paneButtonGroup->setId(ui->pane_button_driver, driver_btn_id);
    ui->paneButtonGroup->setId(ui->pane_button_hmd, hmd_btn_id);
    ui->paneButtonGroup->setId(ui->pane_button_screens, screens_btn_id);
    ui->paneButtonGroup->setId(ui->pane_button_controllers, controller_btn_id);
    ui->paneButtonGroup->setId(ui->pane_button_about, about_btn_id);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pane_button_driver_clicked()
{
    CurrentContent->deleteLater();
    CurrentContent = new Driver_pane(ui->splitter);
    CurrentContent->show();
}

void MainWindow::on_pane_button_clicked(int id)
{
    qDebug() << id;
}
