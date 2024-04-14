#ifndef CONTROLLERS_PANE_H
#define CONTROLLERS_PANE_H

#include <QWidget>

namespace Ui {
class controllers_pane;
}

class controllers_pane : public QWidget
{
    Q_OBJECT

public:
    explicit controllers_pane(QWidget *parent = nullptr);
    ~controllers_pane();

private slots:

private:
    Ui::controllers_pane *ui;
};

#endif // CONTROLLERS_PANE_H
