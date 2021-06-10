#include "infooftask.h"

std::string InfoOfTask::time_t2string(const time_t timep)
{
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}

void InfoOfTask::setAssignmentId(QString assignment)
{
    assignmentId=assignment.toLong();
}

QString InfoOfTask::getDeadline()
{
    if (assignment.getId() == 0)
        assignment = DataManager::Assignment(assignmentId);
    time_t timep = assignment.getDeadline();
    return QString::fromStdString(time_t2string(timep));
}

QString InfoOfTask::getClassName()
{
    if (assignment.getId() == 0)
        assignment = DataManager::Assignment(assignmentId);
    auto _class = DataManager::Class(assignment.getClassId());
    return QString::fromStdString(_class.getName());
}

QString InfoOfTask::getAssignmentName()
{
    if (assignment.getId() == 0)
        assignment = DataManager::Assignment(assignmentId);
    return QString::fromStdString(assignment.getTitle());
}

void InfoOfTask::refresh()
{
    uncheckNum = 0, finishNum = 0;
    while (homeworkList.count()) {
        homeworkList.pop_back();
    }
    while (homeworkFinishList.count()) {
        homeworkFinishList.pop_back();
    }
    while (homeworkUncheckList.count()) {
        homeworkUncheckList.pop_back();
    }
    try {
        auto List = DataManager::getHomeworkListByAsmId(assignmentId);
        if (List.size() > 0)
        {
            for (auto& iter : List)
            {
                auto st = DataManager::Student(iter.getStudentId());
                QJsonObject obj;
                obj.insert("id", QString::fromStdString(std::to_string(iter.getId())));
                obj.insert("name", QString::fromStdString(st.getName()));
                obj.insert("studentId", QString::number(st.getId()));
                obj.insert("studentNum", QString::fromStdString(st.getSchoolNum()));
                obj.insert("status", iter.getStatus());
                obj.insert("score", QString::number(iter.getScore()));

                if (iter.getStatus() == 1)
                {
                    homeworkUncheckList.append(obj);
                    uncheckNum++;
                }

                if (iter.getStatus() == 2)
                {
                    homeworkFinishList.append(obj);
                    finishNum++;
                }
            }
        }
    }
    catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [HomeworkViewController] " << error.what() << Qt::endl;
    }

    homeworkList = homeworkUncheckList + homeworkFinishList;
}

int InfoOfTask::getUncheckNum()
{
    return uncheckNum;
}

int InfoOfTask::getFinishNum()
{
    return finishNum;
}

QJsonArray InfoOfTask::getHomeworkList() {
    return homeworkList;
}

bool InfoOfTask::deleteAssignment() {
    return DataManager::deleteAssignment(assignmentId) == DataManager::SUCCESS;
}
