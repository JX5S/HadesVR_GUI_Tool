#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <QObject>

struct QuatData
{
    double w = 1.;
    double x = 0.;
    double y = 0.;
    double z = 0.;
};

struct ControllerData
{
    uint16_t Ctrl1_Buttons = 0;
    uint8_t Ctrl1_Trigger = 0;
    int8_t Ctrl1_axisX = 0;
    int8_t Ctrl1_axisY = 0;
    int8_t Ctrl1_trackY = 0;
    uint8_t Ctrl1_vBat = 0;
    uint8_t Ctrl1_THUMB = 0;
    uint8_t Ctrl1_INDEX = 0;
    uint8_t Ctrl1_MIDDLE = 0;
    uint8_t Ctrl1_RING = 0;
    uint8_t Ctrl1_PINKY = 0;
    uint8_t Ctrl1_AnalogGrip = 0;
};

class connection_handler : public QObject
{
    Q_OBJECT
public:
    explicit connection_handler(QObject *parent = nullptr);
    ~connection_handler();
public slots:
    void connect();
    void disconnect();
signals:
    void connected();
    void disconnected();
    void HMD_Quat_data(QuatData quatdata);
    void Controller_L_Quat_data(QuatData quatdata);
    void Controller_R_Quat_data(QuatData quatdata);
    void Controller_L_Buttons();
    void Controller_R_Buttons();
};

#endif // CONNECTION_HANDLER_H
