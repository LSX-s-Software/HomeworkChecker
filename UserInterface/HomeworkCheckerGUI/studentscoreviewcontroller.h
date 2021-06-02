#ifndef STUDENTSCOREVIEWCONTROLLER_H
#define STUDENTSCOREVIEWCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include "qqml.h"
#include "DataManager.hpp"

class StudentScoreViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray scoreList READ getScoreList CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    QML_ELEMENT
public:
    explicit StudentScoreViewController(QObject *parent = nullptr);
    
    Q_INVOKABLE void loadData(int stuId, int classId);
    QJsonArray getScoreList();
    QString getName();

private:
    QJsonArray scoreList;
    QString name;
};

#endif // STUDENTSCOREVIEWCONTROLLER_H
