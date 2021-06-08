//
// Created by Raffaele Montella on 01/04/21.
//

#include "Native.hpp"

#include <QDebug>
#include <QProcess>


QImage fairwind::apps::native::Native::getIcon() const {
    return QImage(":resources/images/icons/native_icon.png");
}

QWidget *fairwind::apps::native::Native::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {
    if (args.contains("Command")) {
        QString command=args["Command"].toString();
        QStringList commandArgs;
        commandArgs.empty();
        QProcess::startDetached(command/*,commandArgs*/);
        mainWindow->showMinimized();
    }
    return nullptr;
}

QString fairwind::apps::native::Native::getId() const {
    return fairwind::AppBase::getId();
}

QString fairwind::apps::native::Native::getName() const {
    return fairwind::AppBase::getName();
}

QString fairwind::apps::native::Native::getDesc() const {
    return fairwind::AppBase::getDesc();
}

void fairwind::apps::native::Native::onInit(QJsonObject *metaData) {
    AppBase::onInit(metaData);
}

QWidget *fairwind::apps::native::Native::onSettings(QTabWidget *tabWidgets) {
    return nullptr;
}

QJsonObject fairwind::apps::native::Native::getConfig() {
    return AppBase::getConfig();
}
