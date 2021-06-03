#include "classscoreviewcontroller.h"

ClassScoreViewController::ClassScoreViewController(QObject *parent) : QObject(parent) {
    highestScore = 0;
    lowestScore = 0;
    avgScore = 0;
}

void ClassScoreViewController::getData(long classId) {
    while (scoreList.count()) {
        scoreList.pop_back();
    }
    try {
        std::vector<DataManager::ScoreListItem> list = DataManager::getScoreList(classId);
        if (list.size() == 0)
            return;
        double min = std::numeric_limits<double>::max(), max = 0, sum = 0;
        for (auto item : list) {
            if (item.score > max) {
                max = item.score;
            } else if (item.score < min) {
                min = item.score;
            }
            sum += item.score;
            QJsonObject obj;
            obj.insert("stuId", QString::fromStdString(std::to_string(item.stuId)));
            obj.insert("name", QString::fromStdString(item.name));
            obj.insert("schoolNum", QString::fromStdString(item.schoolNum));
            obj.insert("score", QString::fromStdString(DMUtils::double2FixedStr(item.score, 2)));
            scoreList.append(obj);
        }
        highestScore = max;
        lowestScore = min;
        avgScore = sum / list.size();
    } catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [ClassScoreViewController] " << error.what() << Qt::endl;
    }
}

QJsonArray ClassScoreViewController::getScoreList() {
    return scoreList;
}

double ClassScoreViewController::getHighestScore() {
    return highestScore;
}

double ClassScoreViewController::getAvgScore() {
    return avgScore;
}

double ClassScoreViewController::getLowestScore() {
    return lowestScore;
}

bool ClassScoreViewController::exportData(const QString& path) {
    std::ofstream outFile;
    outFile.open(path.toStdString(), std::ios::out);
    if (outFile.is_open()) {
        //表头
        outFile << "姓名" << ',' << "学号" << ',' << "成绩" << std::endl;
        //数据
        for (long i = 0; i < scoreList.size(); i++) {
            outFile << scoreList.at(i)["name"].toString().toStdString() << ',' << scoreList.at(i)["schoolNum"].toString().toStdString() << ',' << scoreList.at(i)["score"].toString().toStdString() << std::endl;
        }
        outFile.close();
        return true;
    }
    qDebug() << "[ERROR] [ClassScoreViewController] File cannot be opened." << Qt::endl;
    return false;
}
