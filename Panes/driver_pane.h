#ifndef DRIVER_PANE_H
#define DRIVER_PANE_H

#include <QWidget>
#include <QDebug>
#include <QTimer>

#include "generic_pane.h"

namespace Ui {
class Driver_pane;
}

class Driver_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit Driver_pane(QWidget *parent = nullptr);
    ~Driver_pane();
    void enable();
    void disable();

private slots:
    void on_button_steamvr_clicked();

    void on_button_steamvr_driver_clicked();

    void on_button_hadesvr_clicked();

    void on_pushButton_clicked();

    void refresh();

    void on_SettingSelectPushbutton_clicked();

private:
    Ui::Driver_pane *ui;
    bool isSteamInstalled = false;
    bool isSteamVRInstalled = false;
    bool isHadesVRInstalled = false;
    QString SteamVR_drivers_folder = "";
    QTimer timer;
};

#endif // DRIVER_PANE_H
