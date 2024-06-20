#include "vrsettings.h"
#include "QFile"
#include <QDebug>
#include <QMessageBox>

// Here be dragons. Read at your own risk

VRSettings::VRSettings() { // Used as reference, along with QT documentation: https://stackoverflow.com/a/18770335
    QString settingsFile(":/resources/default_settings.json");
    QFile file;
    file.setFileName(settingsFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonDocument tmpD = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject tmpO = tmpD.object();
    foreach(const QString& keyA, tmpO.keys()){
        QJsonObject category = tmpO.value(keyA).toObject();
        foreach(const QString& keyB, category.keys()){
            QJsonValue value = category.value(keyB);
            switch(value.type()){
            case QJsonValue::Bool:
                settingsMap[keyA+":"+keyB] = value.toBool();
                break;
            case QJsonValue::Double:
                settingsMap[keyA+":"+keyB] = value.toDouble();
                break;
            case QJsonValue::String:
                settingsMap[keyA+":"+keyB] = value.toString();
                break;
            default:
                qDebug() << "Unhandled type:" << value.type();
                break;
            }
        }
    }
    qDebug() << settingsMap;
}

VRSettings::~VRSettings(){}

void VRSettings::ReadFromDisk(){
    if (hadesSettingsPath == ""){
        QMessageBox messageBox;
        messageBox.setText("Please input a path for the default.vrsettings file");
        messageBox.exec();
        return;
    }
    if (!QFile::exists(hadesSettingsPath)){
        QMessageBox messageBox;
        messageBox.setText("The path for default.vrsettings isn't valid");
        messageBox.exec();
        return;
    }

    QFile file;
    file.setFileName(hadesSettingsPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonDocument tmpD = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject tmpO = tmpD.object();
    foreach(const QString& keyA, tmpO.keys()){
        QJsonObject category = tmpO.value(keyA).toObject();
        foreach(const QString& keyB, category.keys()){
            QJsonValue value = category.value(keyB);
            switch(value.type()){
            case QJsonValue::Bool:
                settingsMap[keyA+":"+keyB] = value.toBool();
                break;
            case QJsonValue::Double:
                settingsMap[keyA+":"+keyB] = value.toDouble();
                break;
            case QJsonValue::String:
                settingsMap[keyA+":"+keyB] = value.toString();
                break;
            default:
                qDebug() << "Unhandled type:" << value.type();
                break;
            }
        }
    }
    qDebug() << settingsMap;
    emit settingsHaveChagned(this);
}

void VRSettings::SaveToDisk(){
    if (hadesSettingsPath == ""){
        QMessageBox messageBox;
        messageBox.setText("Please input a path for the default.vrsettings file");
        messageBox.exec();
        return;
    }
    if (!QFile::exists(hadesSettingsPath)){
        QMessageBox messageBox;
        messageBox.setText("The path for default.vrsettings isn't valid");
        messageBox.exec();
        return;
    }

    // QT's JSON implementation doesn't maintain order of the data. That hampers human readability, so I had to build this monstrosity
    QFile orderFile;
    orderFile.setFileName(":/resources/order.txt");
    orderFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QFile writeFile;
    writeFile.setFileName(hadesSettingsPath);
    writeFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

    writeFile.write("{\n");
    bool flag = false;
    bool flag2 = false;
    bool newlineflag = false;
    while(!orderFile.atEnd()) {
        static QString category = "";
        QString line = orderFile.readLine();
        if (line == "\n"){
            newlineflag = true;
        } else if (line[0] == 'c'){
            flag2 = false;
            if (flag) writeFile.write("\n   },\n");
            category = line.split("\"")[1];
            QString toWrite = "   	\"";
            toWrite = "   	\"" + category + "\" : {\n";
            writeFile.write(toWrite.toUtf8());
            flag = true; // Don't finish the 0th block, because it doesn't exist
        } else {
            QString valueName = line.split("\"")[1];
            QVariant valueVariant = settingsMap[category+":"+valueName];
            QString value = "";

            switch (valueVariant.typeId()){
            case 1:
                if(valueVariant.toBool()){
                    value = "true";
                } else {
                    value = "false";
                }
                break;
            case 6: // double
            case 2: // int
                value = QString::number(valueVariant.toDouble());
                break;
            case 10:
                value = "\"" + valueVariant.toString() + "\"";
                break;
            default:
                qDebug() << "Unhandled type ID: " << valueVariant.typeId();
                break;
            }
            QString toWrite = "		\"" + valueName + "\" : " + value;
            if (flag2){
                if (newlineflag) writeFile.write(",\n\n");
                else writeFile.write(",\n");
                newlineflag = false;
            }
            flag2 = true;
            writeFile.write(toWrite.toUtf8());
        }
    }
    writeFile.write("\n   }\n}");

    writeFile.close();
    orderFile.close();

    // to refresh UI with what was actually written. Mainly for invalid inputs
    ReadFromDisk();
}


void VRSettings::changePath(QString path){
    hadesSettingsPath = path;
}

void VRSettings::changeSetting(QString key, QVariant value){
    settingsMap[key] = value;
}

