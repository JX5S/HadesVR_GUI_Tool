#ifndef CONTROLLERS_PANE_H
#define CONTROLLERS_PANE_H

#include <QWidget>
#include "generic_pane.h"

namespace Ui {
class controllers_pane;
}

class controllers_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit controllers_pane(QWidget *parent = nullptr);
    ~controllers_pane();
    void enable();
    void disable();
    void updateSettings(VRSettings * vrsettings);

private slots:

private:
    Ui::controllers_pane *ui;
};

#endif // CONTROLLERS_PANE_H
