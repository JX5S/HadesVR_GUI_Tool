#ifndef DRIVER_PANE_H
#define DRIVER_PANE_H

#include <QWidget>

namespace Ui {
class Driver_pane;
}

class Driver_pane : public QWidget
{
    Q_OBJECT

public:
    explicit Driver_pane(QWidget *parent = nullptr);
    ~Driver_pane();

private slots:
    void on_button_steamvr_clicked();

    void on_button_steamvr_driver_clicked();

    void on_button_hadesvr_clicked();

    void on_pushButton_clicked();

    void refresh();

private:
    Ui::Driver_pane *ui;
    bool isSteamInstalled = false;
    bool isSteamVRInstalled = false;
    QString SteamVR_drivers_folder = "";
};

#endif // DRIVER_PANE_H
