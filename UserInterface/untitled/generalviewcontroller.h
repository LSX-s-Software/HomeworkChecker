#ifndef GENERALVIEWCONTROLLER_H
#define GENERALVIEWCONTROLLER_H

#include <QObject>
#include <QString>
#include "qqml.h"

class GeneralViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName)
    Q_PROPERTY(QString correctedCount READ correctedCount)
    Q_PROPERTY(QString submittedCount READ submittedCount)
    Q_PROPERTY(QString correctedProg READ correctedProg)
    QML_ELEMENT
public:
    explicit GeneralViewController(QObject *parent = nullptr);

    QString userName();
    QString correctedCount();
    QString submittedCount();
    QString correctedProg();

};

#endif // GENERALVIEWCONTROLLER_H
