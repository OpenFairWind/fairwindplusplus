//
// Created by Raffaele Montella on 15/07/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QMessageBox>
#include "Entertainment.hpp"
#include "MainPage.hpp"


/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::entertainment::Entertainment::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage(nullptr, this);
    add(mainPage);
    show();
}

void fairwind::apps::entertainment::Entertainment::onCreate() {}

void fairwind::apps::entertainment::Entertainment::onResume() {}

void fairwind::apps::entertainment::Entertainment::onPause() {}

void fairwind::apps::entertainment::Entertainment::onStop() {}

void fairwind::apps::entertainment::Entertainment::onDestroy() {}



void fairwind::apps::entertainment::Entertainment::updateSettings(QString settingsID, QString newValue) {
    FairWindApp::updateSettings(settingsID, newValue);
}