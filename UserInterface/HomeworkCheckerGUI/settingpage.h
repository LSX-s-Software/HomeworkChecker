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
    Q_INVOKABLE QString getWorkPath();
    Q_INVOKABLE void setWorkPath(const QString& path);
};

