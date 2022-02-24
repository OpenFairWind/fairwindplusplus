//
// Created by Raffaele Montella on 01/04/21.
//

#include "External.hpp"

#include <QDebug>
#include <QFile>
#include <QProcess>

namespace fairwind::apps::external {
    void External::onStart() {
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
    
    void External::onCreate() { FairWindApp::onCreate();}
    void External::onResume() { FairWindApp::onResume();}
    void External::onPause() { FairWindApp::onPause();}
    void External::onStop() { FairWindApp::onStop();}
    void External::onDestroy() { FairWindApp::onDestroy();}
    void External::onConfigChanged() { FairWindApp::onConfigChanged();}
    void External::onInstall() { FairWindApp::onInstall();}
    void External::onUninstall() { FairWindApp::onUninstall();}
}