#ifndef OTHERS_PANE_H
#define OTHERS_PANE_H

#include <QWidget>
#include "generic_pane.h"

namespace Ui {
class others_pane;
}

class others_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit others_pane(QWidget *parent = nullptr, VRSettings * vrsettings = nullptr);
    ~others_pane();
    void enable();
    void disable();
    void updateSettings(VRSettings * vrsettings);

private:
    Ui::others_pane *ui;
    VRSettings * vrsettings;
};

#endif // OTHERS_PANE_H
