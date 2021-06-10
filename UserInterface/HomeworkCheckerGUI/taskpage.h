#pragma once
#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <vector>
#include "qqml.h"
#include "DataManager.hpp"
#include "account.h"
#include "WebsocketClientForApp.h"
#include "settingpage.h"

class TaskPage :
    public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray assignmentList READ getAssignmentList CONSTANT)
    Q_PROPERTY(QJsonArray classList READ getClassList CONSTANT)
    QML_ELEMENT
public:
    explicit TaskPage(QObject* parent = nullptr): QObject(parent) {}

    Q_INVOKABLE void refresh();
    QJsonArray getAssignmentList();
    QJsonArray getClassList();
    Q_INVOKABLE bool newAssignment(long classId, QString &title, QString &desc, QString &ddl);

signals:

private:
    QJsonArray assignmentList;
    QJsonArray classList;
    std::string time_t2string(const time_t time_t_time);
};

