#pragma once
#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <vector>
#include "qqml.h"
#include "DataManager.hpp"
#include "account.h"

class TaskPage :
    public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray assignmentList READ getAssignmentList CONSTANT)
    QML_ELEMENT
public:
    explicit TaskPage(QObject* parent = nullptr) {}

    Q_INVOKABLE void refresh();
    QJsonArray getAssignmentList();

signals:

private:
    QJsonArray assignmentList;
    std::string time_t2string(const time_t time_t_time);
};

