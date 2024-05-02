#ifndef VRSETTINGS_H
#define VRSETTINGS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QtCore/QObject>

class VRSettings : public QObject
{
    Q_OBJECT
public:
    VRSettings();
    ~VRSettings();

    QString hadesSettingsPath = "";

    QMap<QString, QVariant> settingsMap;

public slots:
    void changePath(QString path);
    void ReadFromDisk();
    void SaveToDisk();

    void changeSetting(QString key, QVariant value);

signals:
    void settingsHaveChagned(VRSettings * vrsettings);

private:
};

#endif // VRSETTINGS_H
