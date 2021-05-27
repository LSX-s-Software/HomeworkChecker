QT += quick

CONFIG += c++11

# CONFIG += no_autoqmake

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        account.cpp \
        generalviewcontroller.cpp \
        main.cpp \
        settingpage.cpp

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
    account.h \
    generalviewcontroller.h \
    settingpage.h

INCLUDEPATH += /usr/local/Cellar/mysql/8.0.23_1/include/mysql

#macx: LIBS += -L/usr/local/mysql-connector-c++-8.0.25/lib64/ -lcrypto

#macx: LIBS += -L/usr/local/mysql-connector-c++-8.0.25/lib64/ -lssl

macx: LIBS += -L/usr/local/mysql-connector-c++-8.0.25/lib64/ -lmysqlcppconn

INCLUDEPATH += /usr/local/mysql-connector-c++-8.0.25/lib64
DEPENDPATH += /usr/local/mysql-connector-c++-8.0.25/lib64

macx: LIBS += -L../../DataManager/build/Debug/ -lDataManager

macx: PRE_TARGETDEPS += ../../DataManager/build/Debug/libDataManager.a

INCLUDEPATH += ../../DataManager/build/Debug
DEPENDPATH += ../../DataManager/build/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../packages/mysql/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../packages/mysql/lib/ -llibmysql

INCLUDEPATH += $$PWD/../../packages/mysql/include
DEPENDPATH += $$PWD/../../packages/mysql/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../packages/mysql/lib/liblibmysql.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../packages/mysql/lib/liblibmysql.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../packages/mysql/lib/libmysql.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../packages/mysql/lib/libmysql.lib

win32: LIBS += -L$$PWD/../../lib/ -lDataManager

INCLUDEPATH += $$PWD/../../DataManager/DataManager
DEPENDPATH += $$PWD/../../DataManager/DataManager

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib/DataManager.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../lib/libDataManager.a
