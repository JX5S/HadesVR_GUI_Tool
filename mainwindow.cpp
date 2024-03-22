#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Panes/driver_pane.h"
#include "Panes/about_pane.h"
#include "Panes/controllers_pane.h"
#include "Panes/hmd_pane.h"
#include "Panes/screens_pane.h"

#include <QObject>
#include <QVector>
#include <QPair>
#include <QIcon>

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
    QObject::connect(ui->paneButtonGroup, &QButtonGroup::idClicked, this, &MainWindow::on_pane_button_clicked);

    ui->pane_button_controllers->setIcon(QIcon(":/icons/resources/reshot-icon-about-NXKPGA5CMW.svg"));

    panes = {
        Pane(new Driver_pane(ui->stackedWidget), ui->pane_button_driver, "Driver setup", 0),
        Pane(new hmd_pane(ui->stackedWidget), ui->pane_button_hmd, "HMD setup", 1),
        Pane(new screens_pane(ui->stackedWidget), ui->pane_button_screens, "Screens setup", 2),
        Pane(new controllers_pane(ui->stackedWidget), ui->pane_button_controllers, "Controller setup", 3),
        Pane(new about_pane(ui->stackedWidget), ui->pane_button_about, "About program", 4),
    };

    for (Pane pane : panes){
        ui->paneButtonGroup->setId(pane.pane_button, pane.id);
        ui->stackedWidget->addWidget(pane.pane_widget);
//        pane.pane_widget->hide();
    }

    ui->stackedWidget->setCurrentWidget(panes[0].pane_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pane_button_clicked(int id)
{
    qDebug() << id;
    ui->stackedWidget->setCurrentWidget(panes[id].pane_widget);
}
