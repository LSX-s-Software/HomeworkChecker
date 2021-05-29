#pragma once
#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <vector>
#include "qqml.h"
#include "DataManager.hpp"
#include "account.h"

class InfoOfTask :
    public QObject
{
    Q_OBJECT
        Q_PROPERTY(QJsonArray homeworkList READ getHomeworkList CONSTANT)
        QML_ELEMENT
public:
    explicit InfoOfTask(QObject* parent = nullptr) {}

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void setAssignmentId(QString assignment);
    Q_INVOKABLE QString getDeadline();
    Q_INVOKABLE QString getClassName();
    Q_INVOKABLE QString getAssignmentName();
    Q_INVOKABLE int getUncheckNum();
    Q_INVOKABLE int getFinishNum();
    QJsonArray getHomeworkList();

signals:

private:
    QJsonArray homeworkList, homeworkUncheckList, homeworkFinishList;
    int uncheckNum, finishNum;
    long assignmentId;
    DataManager::Assignment assignment;
    std::string time_t2string(const time_t time_t_time);
};

