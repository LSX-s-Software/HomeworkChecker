QT += quick

CONFIG += c++17
DEFINES += WIN32_LEAN_AND_MEAN
# CONFIG += no_autoqmake

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        WebsocketClientForApp.cpp \
        account.cpp \
        classscoreviewcontroller.cpp \
        classviewcontroller.cpp \
        correcthomework.cpp \
        generalviewcontroller.cpp \
        infooftask.cpp \
        main.cpp \
        settingpage.cpp \
        studentscoreviewcontroller.cpp \
        taskpage.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += "../../DataManager/DataManager"

HEADERS += \
    WebsocketClientForApp.h \
    account.h \
    classscoreviewcontroller.h \
    classviewcontroller.h \
    correcthomework.h \
    generalviewcontroller.h \
    infooftask.h \
    settingpage.h \
    studentscoreviewcontroller.h \
    taskpage.h

macx: LIBS += -L../../DataManager/build/Debug/ -lDataManager

macx: PRE_TARGETDEPS += ../../DataManager/build/Debug/libDataManager.a

INCLUDEPATH += ../../DataManager/build/Debug
DEPENDPATH += ../../DataManager/build/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../packages/mysql/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../packages/mysql/lib/ -llibmysql

INCLUDEPATH += ../../packages/mysql/include
DEPENDPATH += ../../packages/mysql/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../packages/mysql/lib/liblibmysql.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../packages/mysql/lib/liblibmysql.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../packages/mysql/lib/libmysql.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../packages/mysql/lib/libmysql.lib

win32: LIBS += -L../../lib/ -lDataManager

INCLUDEPATH += ../../DataManager/DataManager
DEPENDPATH += ../../DataManager/DataManager

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib/DataManager.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../lib/libDataManager.a

INCLUDEPATH += ../../packages/json
INCLUDEPATH += ../../packages/asio/include
INCLUDEPATH += ../../packages/websocketpp/include
DEPENDPATH += ../../packages/json
