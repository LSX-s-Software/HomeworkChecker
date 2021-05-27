#ifndef GENERALVIEWCONTROLLER_H
#define GENERALVIEWCONTROLLER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "qqml.h"
#include "DataManager.hpp"
#include <vector>

class GeneralViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName CONSTANT)
    Q_PROPERTY(QString correctedCount READ correctedCount CONSTANT)
    Q_PROPERTY(QString submittedCount READ submittedCount CONSTANT)
    Q_PROPERTY(QString correctedProg READ correctedProg CONSTANT)
    QML_ELEMENT
public:
    explicit GeneralViewController(QObject *parent = nullptr);

    Q_INVOKABLE void refresh();
    QString userName();
    QString correctedCount();
    QString submittedCount();
    QString correctedProg();

private:
    std::vector<DataManager::Assignment> assmList;
    std::vector<DataManager::Homework> homeworkList;
    long totalClassSize;
};

#endif // GENERALVIEWCONTROLLER_H
