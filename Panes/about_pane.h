#ifndef ABOUT_PANE_H
#define ABOUT_PANE_H

#include <QWidget>
#include "generic_pane.h"

namespace Ui {
class about_pane;
}

class about_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit about_pane(QWidget *parent = nullptr);
    ~about_pane();
    void enable();
    void disable();
    void updateSettings(VRSettings * vrsettings);

private:
    Ui::about_pane *ui;
};

#endif // ABOUT_PANE_H
