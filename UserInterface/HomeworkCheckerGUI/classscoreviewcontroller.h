#ifndef CLASSSCOREVIEWCONTROLLER_H
#define CLASSSCOREVIEWCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include "qqml.h"
#include "DataManager.hpp"
#include <limits>
#include <iostream>
#include <fstream>

class ClassScoreViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray scoreList READ getScoreList CONSTANT)
    Q_PROPERTY(double highestScore READ getHighestScore CONSTANT)
    Q_PROPERTY(double avgScore READ getAvgScore CONSTANT)
    Q_PROPERTY(double lowestScore READ getLowestScore CONSTANT)
    QML_ELEMENT
public:
    explicit ClassScoreViewController(QObject *parent = nullptr);
    
    Q_INVOKABLE void getData(long classId);
    QJsonArray getScoreList();
    double getHighestScore();
    double getAvgScore();
    double getLowestScore();
    Q_INVOKABLE bool exportData(const QString& path);

private:
    QJsonArray scoreList;
    double highestScore;
    double avgScore;
    double lowestScore;
};

#endif // CLASSSCOREVIEWCONTROLLER_H
