//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Radar.hpp"
#include "MainPage.hpp"


void fairwind::apps::radar::Radar::onCreate() {
    FairWindApp::onCreate();
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::radar::Radar::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage();
    add(mainPage);
    show();
}


void fairwind::apps::radar::Radar::onResume() {
    FairWindApp::onResume();
}

void fairwind::apps::radar::Radar::onPause() {
    FairWindApp::onPause();
}

void fairwind::apps::radar::Radar::onStop() {
    FairWindApp::onStop();
}

void fairwind::apps::radar::Radar::onDestroy() {
    FairWindApp::onDestroy();
}


void fairwind::apps::radar::Radar::updateSettings(QString settingsID, QString newValue) {
    FairWindApp::updateSettings(settingsID, newValue);
}