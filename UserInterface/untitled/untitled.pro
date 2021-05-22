QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Images/add.png \
    Images/at.png \
    Images/email.png \
    Images/email-1.png \
    Images/homework.png \
    Images/moren.png \
    Images/progress.png \
    Images/server.png \
    Images/server-1.png \
    Images/weixian.png \
    Images/zonglan.png \
    Images/组 2.png \
    Images/close.png \
    Images/btn.png \
    Images/addBtn.png
