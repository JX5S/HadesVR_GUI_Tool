#ifndef SCREENS_PANE_H
#define SCREENS_PANE_H

#include <QWidget>

#include "generic_pane.h"
#include <QButtonGroup>

namespace Ui {
class screens_pane;
}

class screens_pane : public generic_pane
{
    Q_OBJECT

public:
    explicit screens_pane(QWidget *parent = nullptr);
    ~screens_pane();
    void enable();
    void disable();
    void updateSettings(VRSettings * vrsettings);

public slots:
    void refresh();
    void buttonClicked(int id);

private slots:
    void on_lineEditWindowWidth_textEdited(const QString &arg1);

    void on_lineEditWindowHeight_textEdited(const QString &arg1);

    void on_lineEditRenderWidth_textEdited(const QString &arg1);

    void on_lineEditRenderHeight_textEdited(const QString &arg1);

    void on_lineEditDispRefreshRate_textEdited(const QString &arg1);

    void on_lineEditWindowX_textEdited(const QString &arg1);

    void on_lineEditWindowY_textEdited(const QString &arg1);

private:
    Ui::screens_pane *ui;
    QButtonGroup screenButtonGroup;
    QList<QScreen *> screens;
    void drawScreens(int id);
};

#endif // SCREENS_PANE_H
