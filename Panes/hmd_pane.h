#ifndef HMD_PANE_H
#define HMD_PANE_H

#include <QWidget>
#include <QSerialPortInfo>

namespace Ui {
class hmd_pane;
}

class hmd_pane : public QWidget
{
    Q_OBJECT

public:
    explicit hmd_pane(QWidget *parent = nullptr);
    ~hmd_pane();

private slots:
    void on_COM_Box_currentIndexChanged(int index);

private:
    Ui::hmd_pane *ui;
    QList<QSerialPortInfo> ports;
};

#endif // HMD_PANE_H
