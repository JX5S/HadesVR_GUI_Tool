#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Panes/Pane_class.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pane_button_clicked(int id);

private:
    Ui::MainWindow *ui;
    QWidget * CurrentContent;
    QVector<Pane> panes;
};

#endif // MAINWINDOW_H
