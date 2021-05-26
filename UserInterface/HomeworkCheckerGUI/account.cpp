#include "account.h"

Account::Account(QObject *parent) : QObject(parent) {}

int Account::reg(QString userName, QString password) {
    return user.reg(userName.toStdString(), password.toStdString());
}

int Account::login(QString userName, QString password) {
    return user.login(userName.toStdString(), password.toStdString());
}

QString Account::getName() {
    return QString::fromStdString(user.getName());
}

void Account::setName(const QString &name) {
    user.setName(name.toStdString());
}
