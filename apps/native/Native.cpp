//
// Created by Raffaele Montella on 01/04/21.
//

#include "Native.hpp"

#include <QDebug>
#include <QProcess>


QImage fairwind::apps::native::Native::getIcon() const {
    return QImage(":resources/images/icons/native_icon.png");
}

QWidget *fairwind::apps::native::Native::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    if (args.find("Command")!=args.end()) {
        QString command=args["Command"];
        QStringList commandArgs;
        commandArgs.empty();
        QProcess::startDetached(command/*,commandArgs*/);
        mainWindow->showMinimized();
    }
    return nullptr;
}

QString fairwind::apps::native::Native::getId() const {
    return fairwind::FairWindAppBase::getId();
}

QString fairwind::apps::native::Native::getName() const {
    return fairwind::FairWindAppBase::getName();
}

QString fairwind::apps::native::Native::getDesc() const {
    return fairwind::FairWindAppBase::getDesc();
}

void fairwind::apps::native::Native::init(QJsonObject *metaData) {
    FairWindAppBase::init(metaData);
}
