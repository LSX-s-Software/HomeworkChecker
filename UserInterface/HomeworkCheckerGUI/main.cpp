#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "../../DataManager/DataManager/DataManager.hpp"
//自定义CPP模块头文件
#include "generalviewcontroller.h"
#include "account.h"
#include "classviewcontroller.h"
#include "settingpage.h"
#include "taskpage.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    //自定义CPP模块
    qmlRegisterType<GeneralViewController>("GeneralVC",1,0,"GeneralVC");
    qmlRegisterType<Account>("Account",1,0,"Account");
    qmlRegisterType<SettingPage>("MySettingPage", 1, 0, "MySettingPage");
    qmlRegisterType<ClassViewController>("ClassVC", 1, 0, "ClassVC");
    qmlRegisterType<TaskPage>("AssignmentVC", 1, 0, "AssignmentVC");


    QQmlApplicationEngine engine;
    //engine.rootContext()->setContextProperty("settingPage", new SettingPage(qApp));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    DBManager::DBAccount remote;
    remote.host = "vps.coyangjr.cn";
    remote.username = "root";
    remote.password = "Whu2020";
    DataManager::connectDatabase(remote);
    QObject::connect(qApp, &QGuiApplication::aboutToQuit, [&]{
        //退出 事件循环 前，保存数据
        DataManager::disconnectDatabase();
    });
    engine.load(url);

    return app.exec();
}
