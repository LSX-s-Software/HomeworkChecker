#include "taskpage.h"

std::string TaskPage::time_t2string(const time_t time_t_time)
{
    char szTime[100] = { '\0' };

    tm* pTm = new tm;
    localtime_s(pTm, &time_t_time);
    //pTm = localtime(&time_t_time);
    pTm->tm_year += 1900;
    pTm->tm_mon += 1;

    sprintf_s(szTime, u8"%04dÄê%02dÔÂ%02dÈÕ %02d:%02d:%02d",
        pTm->tm_year,
        pTm->tm_mon,
        pTm->tm_mday,
        pTm->tm_hour,
        pTm->tm_min,
        pTm->tm_sec);

    std::string strTime = szTime;

    delete pTm;
    pTm = NULL;

    return strTime;
}

void TaskPage::refresh()
{
    while (assignmentList.count()) {
        assignmentList.pop_back();
    }
    try {
        auto list = DataManager::getAssignmentList(Account::getId());
        auto studentList = DataManager::getStudentList(list.at(0).getClassId());
        int totolNum = studentList.size();
        for (auto item : list) {
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
    catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [ClassViewController] " << error.what() << Qt::endl;
    }
}

QJsonArray TaskPage::getAssignmentList() {
    return assignmentList;
}