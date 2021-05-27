#ifndef CLASSVIEWCONTROLLER_H
#define CLASSVIEWCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <vector>
#include "qqml.h"
#include "DataManager.hpp"
#include "account.h"

class ClassViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray classList READ getClassList CONSTANT)
    QML_ELEMENT
public:
    explicit ClassViewController(QObject *parent = nullptr);
    
    Q_INVOKABLE void refresh();
    QJsonArray getClassList();
    Q_INVOKABLE int addClass(QString name, QString location, QString time, QString code);
    Q_INVOKABLE int endClass(long id);

signals:

private:
    QJsonArray classList;
};

#endif // CLASSVIEWCONTROLLER_H
