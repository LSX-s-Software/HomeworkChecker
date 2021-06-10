#include "account.h"

DataManager::User Account::user = DataManager::User();

Account::Account(QObject *parent) : QObject(parent) {}

bool Account::connectDB() {
    return DataManager::connectDatabase();
}

int Account::reg(QString userName, QString password) {
    return user.reg(userName.toStdString(), password.toStdString());
}

int Account::login(QString userName, QString password) {
    return user.login(userName.toStdString(), password.toStdString());
}

int Account::getId() {
    return user.getId();
}

QString Account::getName() {
    return QString::fromStdString(user.getName());
}

void Account::setName(const QString &name) {
    if (name.toStdString() == user.getName()) return;
    DataManager::DMErrorType code = user.setName(name.toStdString());
    if (code != DataManager::DMErrorType::SUCCESS) {
        qDebug() << DataManager::DMError(code).what() << Qt::endl;
    }
}
