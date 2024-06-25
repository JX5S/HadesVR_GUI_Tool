#ifndef VRSETTINGS_H
#define VRSETTINGS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QtCore/QObject>

// Class for holding current settings. Works as a map, where key is "category:setting". Also handles JSONs

class VRSettings : public QObject
{
    Q_OBJECT
public:
    VRSettings();
    ~VRSettings(){}

    QString hadesSettingsPath = "";

    QMap<QString, QVariant> settingsMap;

public slots:
    void changePath(QString path);
    void ReadFromDisk();
    void SaveToDisk();

    void changeSetting(QString key, QVariant value); // ui element changes setting

signals:
    void settingsHaveChagned(VRSettings * vrsettings); // Notitfy UI elements

private:
};

#endif // VRSETTINGS_H
