#pragma once
#include <QObject>
#include <QString>
#include "qqml.h"

class SettingPage :
    public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit SettingPage(QObject* parent = nullptr);
    Q_INVOKABLE static QString getWorkPath();
    static std::string getWorkPath_str();
    Q_INVOKABLE static void setWorkPath(const QString& path);
    Q_INVOKABLE static QString getWsClientUrl();
    static std::string getWsClientUrl_str();
    Q_INVOKABLE static void setWsClientUrl(const QString& url);
    Q_INVOKABLE static void loadFromFile();
    Q_INVOKABLE static void saveToFile();
    
private:
    static std::string wsClientUrl;
    static std::string workPath;
    static void restoreFile();
};

