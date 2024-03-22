#ifndef PANE_CLASS_H
#define PANE_CLASS_H

#include <QWidget>
#include <QString>
#include <QToolButton>

struct Pane{
    QWidget * pane_widget;
    QToolButton * pane_button;
    QString name;
    int id;
    Pane(QWidget * pane_widget, QToolButton * pane_button, QString name, int id){
        this->pane_widget = pane_widget;
        this->pane_button = pane_button;
        this->name = name;
        this->id = id;
    }
};

#endif // PANE_CLASS_H
