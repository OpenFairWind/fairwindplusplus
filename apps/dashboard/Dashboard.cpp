//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include <QDebug>
#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/ILayout.hpp>
#include "MainPage.hpp"


void fairwind::apps::dashboard::Dashboard::onCreate() {}

void fairwind::apps::dashboard::Dashboard::onResume()  {}

void fairwind::apps::dashboard::Dashboard::onPause()  {}

void fairwind::apps::dashboard::Dashboard::onStop()  {}

void fairwind::apps::dashboard::Dashboard::onDestroy()  {}

void fairwind::apps::dashboard::Dashboard::onStart() {
    FairWindApp::onStart();

    QString route = getRoute();
    if (route.isEmpty()) {
        route = "__home__";
    }

    auto mainPage = new MainPage(nullptr, this);

    add(mainPage,route);

    show(route);
}

fairwind::apps::dashboard::Dashboard::~Dashboard() {
}



void fairwind::apps::dashboard::Dashboard::updateSettings(QString settingsID, QString newValue) {
    FairWindApp::updateSettings(settingsID, newValue);
}
