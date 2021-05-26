#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QString>
#include "qqml.h"
#include "DataManager.hpp"

class Account: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString userName READ getName WRITE setName)
    QML_ELEMENT
public:
    explicit Account(QObject *parent = nullptr);
    Q_INVOKABLE int reg(QString userName, QString password);
    Q_INVOKABLE int login(QString userName, QString password);
    QString getName();
    void setName(const QString &name);
    
private:
    DataManager::User user;
};

#endif // ACCOUNT_H
