#include "taskpage.h"

std::string TaskPage::time_t2string(const time_t timep)
{
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}

void TaskPage::refresh()
{
    while (assignmentList.count()) {
        assignmentList.pop_back();
    }
    while (classList.count()) {
        classList.pop_back();
    }
    try {
        auto list = DataManager::getAssignmentList(Account::getId());
        if (list.size() > 0)
        {
            auto studentList = DataManager::getStudentList(list.at(0).getClassId());
            int totolNum = studentList.size();
            for (auto& item : list)
            {
                QJsonObject obj;
                obj.insert("id", QString::fromStdString(std::to_string(item.getId())));
                obj.insert("name", QString::fromStdString(item.getTitle()));
                time_t timep = item.getDeadline();
                obj.insert("deadline", QString::fromStdString(time_t2string(timep)));
                auto homeworkList = DataManager::getHomeworkListByAsmId(item.getId());
                int submitNum = homeworkList.size();
                obj.insert("submitted", QString::number(submitNum));
                obj.insert("notSubmitted", QString::number(totolNum - submitNum));
                assignmentList.append(obj);
            }
        }
        std::vector<DataManager::Class> cList = DataManager::getClassList(Account::getId());
        for (auto item : cList) {
            QJsonObject obj;
            obj.insert("modelData", QString::fromStdString(item.getName()));
            obj.insert("id", QString::fromStdString(std::to_string(item.getId())));
            classList.append(obj);
        }
    }
    catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [AssignmentViewController] " << error.what() << Qt::endl;
    }
}

QJsonArray TaskPage::getAssignmentList() {
    return assignmentList;
}

QJsonArray TaskPage::getClassList() {
    return classList;
}

bool TaskPage::newAssignment(int classIndex, QString &title, QString &desc, QString &ddl) {
    try {
        DataManager::Assignment(Account::getId(), title.toStdString(), desc.toStdString(), ddl.toLong(), classList.at(classIndex)["id"].toInt());
        return true;
    } catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [AssignmentViewController] " << error.what() << Qt::endl;
        return false;
    }
}
