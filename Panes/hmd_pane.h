#ifndef HMD_PANE_H
#define HMD_PANE_H

#include <QWidget>

namespace Ui {
class hmd_pane;
}

class hmd_pane : public QWidget
{
    Q_OBJECT

public:
    explicit hmd_pane(QWidget *parent = nullptr);
    ~hmd_pane();

private:
    Ui::hmd_pane *ui;
};

#endif // HMD_PANE_H
