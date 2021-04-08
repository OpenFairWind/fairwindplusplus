//
// Created by Raffaele Montella on 01/04/21.
//

#include "Native.hpp"

#include <QDebug>
#include <QProcess>
#include <include/FairWindExtension.hpp>


QImage fairwind::extensions::plugins::native::Native::getIcon() const {
    return QImage(":resources/images/icons/native_icon.png");
}

QWidget *fairwind::extensions::plugins::native::Native::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    if (args.find("Command")!=args.end()) {
        QString command=args["Command"];
        QStringList commandArgs;
        commandArgs.empty();
        QProcess::startDetached(command/*,commandArgs*/);
        mainWindow->showMinimized();
    }
    return nullptr;
}

QString fairwind::extensions::plugins::native::Native::getId() const {
    return fairwind::extensions::FairWindExtension::getId();
}

QString fairwind::extensions::plugins::native::Native::getName() const {
    return fairwind::extensions::FairWindExtension::getName();
}

QString fairwind::extensions::plugins::native::Native::getDesc() const {
    return fairwind::extensions::FairWindExtension::getDesc();
}

void fairwind::extensions::plugins::native::Native::init(QJsonObject *metaData) {
    FairWindExtension::init(metaData);
}
