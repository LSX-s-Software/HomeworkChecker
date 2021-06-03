#include "generalviewcontroller.h"
#include "account.h"
#include <iostream>

GeneralViewController::GeneralViewController(QObject *parent) : QObject(parent) {}

void GeneralViewController::refresh() {
    try {
        totalClassSize = DataManager::getTotalClassSize(Account::getId());
        assmList = DataManager::getAssignmentList(Account::getId());
        for (auto item : assmList) {
            std::vector<DataManager::Homework> hList = DataManager::getHomeworkListByAsmId(item.getId());
            homeworkList.insert(homeworkList.begin(), hList.begin(), hList.end());
        }
    } catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [GeneralViewController] " << error.what() << Qt::endl;
    }
}

QString GeneralViewController::userName() {
    return Account::getName();
}

QString GeneralViewController::correctedCount() {
    if (homeworkList.size() == 0) {
        return u8"无作业";
    } else if (totalClassSize == 0) {
        return u8"无班级";
    } else {
        int sum = 0;
        for (auto item : homeworkList) {
            if (item.getStatus() == 2) {
                sum++;
            }
        }
        return QString::fromStdString(std::to_string(sum) + "/" + std::to_string(homeworkList.size()));
    }
}

QString GeneralViewController::submittedCount() {
    if (homeworkList.size() == 0) {
        return u8"无作业";
    } else if (totalClassSize == 0) {
        return u8"无班级";
    } else {
        return QString::fromStdString(std::to_string(homeworkList.size()) + "/" + std::to_string(totalClassSize));
    }
}

QString GeneralViewController::correctedProg() {
    if (homeworkList.size() == 0) {
        return u8"未布置作业";
    } else if (totalClassSize == 0) {
        return u8"未创建班级";
    } else {
        int correctedCount = 0;
        for (auto it : homeworkList) {
            correctedCount++;
        }
        double prog = double(correctedCount) / double(assmList.size()) * 100;
        return QString::fromStdString(DMUtils::double2FixedStr(prog, 2) + "%");
    }
}
