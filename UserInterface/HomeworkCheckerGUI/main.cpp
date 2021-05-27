#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

//自定义CPP模块头文件
#include "generalviewcontroller.h"
#include "account.h"
#include "settingpage.h"

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

    QQmlApplicationEngine engine;
    //engine.rootContext()->setContextProperty("settingPage", new SettingPage(qApp));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
