#include "classviewcontroller.h"

ClassViewController::ClassViewController(QObject *parent) : QObject(parent) {}

void ClassViewController::refresh() {
    for (int i = 0; i < classList.size(); i++) {
        classList.removeAt(i);
    }
    try {
        std::vector<DataManager::Class> list = DataManager::getClassList(Account::getId());
        for (auto item : list) {
            QJsonObject obj;
            obj.insert("id", QString::fromStdString(std::to_string(item.getId())));
            obj.insert("name", QString::fromStdString(item.getName()));
            obj.insert("time", QString::fromStdString(item.getTime()));
            obj.insert("location", QString::fromStdString(item.getLocation()));
            obj.insert("code", QString::fromStdString(item.getInviteCode()));
            obj.insert("status", item.getStatus());
            obj.insert("count", item.getSize());
            classList.append(obj);
        }
    } catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [ClassViewController] " << error.what() << Qt::endl;
    }
}

QJsonArray ClassViewController::getClassList() {
    return classList;
}

int ClassViewController::addClass(QString name, QString location, QString time, QString code) {
    try {
        DataManager::Class cla(Account::getId(), name.toStdString(), location.toStdString(), time.toStdString());
        DataManager::DMErrorType errCode = cla.setInviteCode(code.toStdString());
        if (errCode == DataManager::DMErrorType::TARGET_EXISTED)
            return 1;
        else if (errCode == DataManager::DMErrorType::SUCCESS)
            return 0;
        else {
            qDebug() << "[ERROR] [ClassViewController] DMErrorCode=" << errCode << Qt::endl;
            return 3;
        }
    } catch (DataManager::DMException::TARGET_EXISTED) {
        return 2;
    } catch (DataManager::DMError) {
        return 3;
    }
}

int ClassViewController::endClass(long id) {
    DataManager::Class c = DataManager::Class(id);
    return c.endClass();
}
