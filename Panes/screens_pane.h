#ifndef SCREENS_PANE_H
#define SCREENS_PANE_H

#include <QWidget>

#include "generic_pane.h"

namespace Ui {
class screens_pane;
}

class screens_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit screens_pane(QWidget *parent = nullptr);
    ~screens_pane();
    void enable();
    void disable();
    void updateSettings(VRSettings * vrsettings);

public slots:
    void refresh();

private:
    Ui::screens_pane *ui;
};

#endif // SCREENS_PANE_H
