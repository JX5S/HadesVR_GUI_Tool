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
#include <QImage>
#include <QGuiApplication>
#include <QStyleHints>

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

    bool darkmode = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
    qDebug() << "Darkmode:" << darkmode;


    panes = {
        Pane(new Driver_pane(ui->stackedWidget), ui->pane_button_driver, "Driver setup", 0, ":/resources/icons/icons_driver.png"),
        Pane(new hmd_pane(ui->stackedWidget), ui->pane_button_hmd, "HMD setup", 1, ":/resources/icons/icons_hmd.png"),
        Pane(new screens_pane(ui->stackedWidget), ui->pane_button_screens, "Screens setup", 2, ":/resources/icons/icons_screens.png"),
        Pane(new controllers_pane(ui->stackedWidget), ui->pane_button_controllers, "Controller setup", 3, ":/resources/icons/icons_controller.png"),
        Pane(new about_pane(ui->stackedWidget), ui->pane_button_about, "About program", 4, ":/resources/icons/icons_info.png"),
    };

    for (auto pane = panes.begin(); pane != panes.end(); pane++){
        ui->paneButtonGroup->setId(pane->pane_button, pane->id);
        ui->stackedWidget->addWidget(pane->pane_widget);

        QImage original(pane->icon);
        if (darkmode) original.invertPixels();
        QPixmap pixmap(QPixmap::fromImage(original));
        pane->pane_button->setIcon(QIcon(pixmap));
        pane->pane_button->setIconSize(QSize(100,100)); // maximum. Icon won't scale above original resolution, for whatever reason
    }

    ui->stackedWidget->setCurrentWidget(panes[0].pane_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pane_button_clicked(int id)
{
    static int old_id = 0;
    panes[old_id].pane_widget->disable();
    old_id = id;
    ui->stackedWidget->setCurrentWidget(panes[id].pane_widget);
    panes[id].pane_widget->enable();
}
