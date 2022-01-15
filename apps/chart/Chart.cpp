//
// Created by Raffaele Montella on 05/04/21.
//

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <QLabel>
#include <QFile>
#include <FairWindSdk/IDisplay.hpp>
#include <FairWindSdk/displays/DisplayChart.hpp>
#include "Chart.hpp"
#include "MainPage.hpp"

// Called by the FairWind framework when the app is invoked for the first time
void fairwind::apps::chart::Chart::onStart() {

    FairWindApp::onStart();

    auto mainPage = new MainPage(nullptr, this);
    add(mainPage);

    show();
}

void fairwind::apps::chart::Chart::updateSettings(QString settingsID, QString newValue) {
    FairWindApp::updateSettings(settingsID, newValue);
}

void fairwind::apps::chart::Chart::onCreate() {
}

void fairwind::apps::chart::Chart::onResume() {
}

void fairwind::apps::chart::Chart::onPause() {
}

void fairwind::apps::chart::Chart::onStop() {
}

void fairwind::apps::chart::Chart::onDestroy() {
}


