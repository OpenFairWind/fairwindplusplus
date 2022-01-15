//
// Created by Raffaele Montella on 01/04/21.
//

#include "External.hpp"

#include <QDebug>
#include <QFile>
#include <QProcess>

void fairwind::apps::external::External::onStart() {
    FairWindApp::onStart();

    QMap<QString, QVariant> args = getArgs();

    if (args.contains("Command")) {
        QString command=args["Command"].toString();
        QStringList commandArgs;
        commandArgs.empty();
        QProcess::startDetached(command/*,commandArgs*/);
        auto mainWindow = FairWind::getInstance()->getMainWindow();
        mainWindow->showMinimized();
    }
}

void fairwind::apps::external::External::onCreate() {}
void fairwind::apps::external::External::onResume() {}
void fairwind::apps::external::External::onPause() {}
void fairwind::apps::external::External::onStop() {}
void fairwind::apps::external::External::onDestroy() {}

void fairwind::apps::external::External::updateSettings(QString settingsID, QString newValue) {
    FairWindApp::updateSettings(settingsID, newValue);
}