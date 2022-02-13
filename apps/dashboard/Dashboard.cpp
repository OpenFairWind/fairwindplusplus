//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include <QDebug>
#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/ILayout.hpp>
#include "MainPage.hpp"


void fairwind::apps::dashboard::Dashboard::onCreate() { FairWindApp::onCreate(); }

void fairwind::apps::dashboard::Dashboard::onResume()  { FairWindApp::onResume(); }

void fairwind::apps::dashboard::Dashboard::onPause()  { FairWindApp::onPause(); }

void fairwind::apps::dashboard::Dashboard::onStop()  { FairWindApp::onStop(); }

void fairwind::apps::dashboard::Dashboard::onDestroy()  { FairWindApp::onDestroy(); }

void fairwind::apps::dashboard::Dashboard::onConfigChanged()  { FairWindApp::onConfigChanged(); }

void fairwind::apps::dashboard::Dashboard::onStart() {
    FairWindApp::onStart();

    QString route = getRoute();
    if (route.isEmpty()) {
        route = "__home__";
    }

    auto mainPage = new MainPage();

    add(mainPage,route);

    show(route);
}

fairwind::apps::dashboard::Dashboard::~Dashboard() {
}
