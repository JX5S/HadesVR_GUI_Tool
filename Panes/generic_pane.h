#ifndef GENERIC_PANE_H
#define GENERIC_PANE_H

#include <QWidget>

class generic_pane : public QWidget
{
    Q_OBJECT
public:
    explicit generic_pane(QWidget *parent = nullptr);
signals:
public slots:
    virtual void enable() = 0;
    virtual void disable() = 0;
};

#endif // GENERIC_PANE_H
