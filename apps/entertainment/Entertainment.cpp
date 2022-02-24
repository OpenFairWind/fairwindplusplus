//
// Created by Raffaele Montella on 15/07/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QMessageBox>
#include "Entertainment.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::entertainment {
/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void Entertainment::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage();
    add(mainPage);
    show();
}

void Entertainment::onCreate() { FairWindApp::onCreate();}

void Entertainment::onResume() { FairWindApp::onResume();}

void Entertainment::onPause() { FairWindApp::onPause();}

void Entertainment::onStop() { FairWindApp::onStop();}

void Entertainment::onDestroy() { FairWindApp::onDestroy();}

void Entertainment::onConfigChanged() { FairWindApp::onConfigChanged();}

void Entertainment::onInstall()  { FairWindApp::onInstall();}

void Entertainment::onUninstall() { FairWindApp::onUninstall();}

}