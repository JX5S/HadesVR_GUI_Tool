#ifndef ABOUT_PANE_H
#define ABOUT_PANE_H

#include <QWidget>

namespace Ui {
class about_pane;
}

class about_pane : public QWidget
{
    Q_OBJECT

public:
    explicit about_pane(QWidget *parent = nullptr);
    ~about_pane();

private:
    Ui::about_pane *ui;
};

#endif // ABOUT_PANE_H
