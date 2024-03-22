#ifndef SCREENS_PANE_H
#define SCREENS_PANE_H

#include <QWidget>

namespace Ui {
class screens_pane;
}

class screens_pane : public QWidget
{
    Q_OBJECT

public:
    explicit screens_pane(QWidget *parent = nullptr);
    ~screens_pane();

private:
    Ui::screens_pane *ui;
};

#endif // SCREENS_PANE_H
