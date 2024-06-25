#ifndef GENERIC_PANE_H
#define GENERIC_PANE_H

#include <QWidget>
#include "vrsettings.h"

// Defines functions available to all panes. Makes it possible to have an array of type "generic_pane*" include all panes

class generic_pane : public QWidget
{
    Q_OBJECT
public:
    explicit generic_pane(QWidget *parent = nullptr);
signals:
    void changeSettingMemory(QString key, QVariant value);
public slots:
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual void updateSettings(VRSettings * vrsettings) = 0;
};

#endif // GENERIC_PANE_H
