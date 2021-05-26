#include "generalviewcontroller.h"

GeneralViewController::GeneralViewController(QObject *parent) : QObject(parent) {}

QString GeneralViewController::userName() {
    return "张三";
}

QString GeneralViewController::correctedCount() {
    return "22/30";
}

QString GeneralViewController::submittedCount() {
    return "28/30";
}

QString GeneralViewController::correctedProg() {
    return "3/4";
}
