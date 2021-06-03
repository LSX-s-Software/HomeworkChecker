#include "studentscoreviewcontroller.h"

StudentScoreViewController::StudentScoreViewController(QObject *parent) : QObject(parent) {}

void StudentScoreViewController::loadData(int stuId, int classId) {
    while (scoreList.count()) {
        scoreList.pop_back();
    }
    try {
        std::vector<DataManager::CompleteHomeworkList> list = DataManager::getHomeworkListByStuId(stuId, classId);
        if (list.size() == 0)
            return;
        for (auto item : list) {
            QJsonObject obj;
            if (item.homework.isEmpty()) {
                obj.insert("name", QString::fromStdString(item.assignment.getTitle()));
                obj.insert("score", "未完成（0）");
            } else {
                obj.insert("name", QString::fromStdString(item.assignment.getTitle()));
                obj.insert("score", QString::fromStdString(DMUtils::double2FixedStr(item.homework.getScore(), 2)));
            }
            scoreList.append(obj);
        }
    } catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [StudentScoreViewController] " << error.what() << Qt::endl;
    }
}

QJsonArray StudentScoreViewController::getScoreList() {
    return scoreList;
}

QString StudentScoreViewController::getName() {
    return name;
}
