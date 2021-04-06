//
// Created by Raffaele Montella on 01/04/21.
//

#include "Native.hpp"

#include <QDebug>
#include <QProcess>


QImage fairwind::extensions::plugins::native::Native::getIcon() const {
    return QImage(":resources/images/icons/native_icon.png");
}

QString fairwind::extensions::plugins::native::Native::getId() const {
    return FairWindExtension::getId();
}

QString fairwind::extensions::plugins::native::Native::getName() const {
    return FairWindExtension::getName();
}

QString fairwind::extensions::plugins::native::Native::getDesc() const {
    return FairWindExtension::getDesc();
}

void fairwind::extensions::plugins::native::Native::setMetaData(QJsonObject &metaData) {
    FairWindExtension::setMetaData(metaData);
}

QWidget *fairwind::extensions::plugins::native::Native::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {
    if (args.find("Command")!=args.end()) {
        QString command=args["Command"];
        QProcess::startDetached(command);
        mainWindow->showMinimized();
    }
    return nullptr;
}
