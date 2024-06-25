#ifndef PANE_CLASS_H
#define PANE_CLASS_H

#include <QWidget>
#include <QString>
#include <QToolButton>
#include "generic_pane.h"

// Holds information about a pane. Just a basic struct, not even a QOBJECT

struct Pane{
    generic_pane * pane_widget;
    QToolButton * pane_button;
    QString name;
    int id;
    QString icon;
    Pane(generic_pane * pane_widget, QToolButton * pane_button, QString name, int id, QString icon){
        this->pane_widget = pane_widget;
        this->pane_button = pane_button;
        this->name = name;
        this->id = id;
        this->icon = icon;
    }
};

#endif // PANE_CLASS_H
