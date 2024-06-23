#ifndef CONTROLLERS_PANE_H
#define CONTROLLERS_PANE_H

#include <QWidget>
#include "generic_pane.h"
#include "generic_setting.h"
#include "vrsettings.h"

namespace Ui {
class controllers_pane;
}

class controllers_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit controllers_pane(QWidget *parent = nullptr, VRSettings * vrsettings = nullptr);
    ~controllers_pane();
    void enable();
    void disable();
    void updateSettings(VRSettings * vrsettings);

signals:
    void updateControllerSettings(VRSettings * vrsettings);

private slots:
    void on_checkBoxEnableControllers_toggled(bool checked);

    void on_comboBoxControllerType_currentIndexChanged(int index);

    void on_checkBoxAccelerometers_toggled(bool checked);

private:
    Ui::controllers_pane *ui;
    VRSettings * vrsettings;
    QVector<generic_setting *> auto_settings;
};

#endif // CONTROLLERS_PANE_H
