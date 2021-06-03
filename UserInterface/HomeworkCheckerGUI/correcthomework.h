#pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif
#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <qfile.h>
#include <vector>
#include "qqml.h"
#include "DataManager.hpp"
#include "account.h"

class CorrectHomework :
    public QObject
{
    Q_OBJECT
        Q_PROPERTY(QString text READ getText CONSTANT)
        Q_PROPERTY(QJsonArray attachmentList READ getAttachmentList CONSTANT)
        //Q_PROPERTY(QString homeworkId WRITE setHomeworkId)
        QML_ELEMENT
public:
    explicit CorrectHomework(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void initLoad();
    Q_INVOKABLE QString getText();
    Q_INVOKABLE QJsonArray getAttachmentList();
    Q_INVOKABLE bool downloadFile(QString fileName);
    Q_INVOKABLE void setHomeworkId(QString homeworkId);
    Q_INVOKABLE QString getWorkPath();

    Q_INVOKABLE void submit(QString comment, QString score);

signals:

private:
    long homeworkId;
    QString text;
    QString homeworkId_qstr;
    QStringList contentList, attachmentList;
    QJsonArray attachmentArray;
    QString rootPath;
    QByteArray readFile(QFile file);
};