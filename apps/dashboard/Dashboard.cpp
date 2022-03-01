//
// Created by Raffaele Montella on 01/04/21.
//

#include "Dashboard.hpp"
#include <QDebug>
#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/ILayout.hpp>
#include "MainPage.hpp"

namespace fairwind::apps::dashboard {
    void Dashboard::onCreate() { FairWindApp::onCreate(); }

    void Dashboard::onResume() { FairWindApp::onResume(); }

    void Dashboard::onPause() { FairWindApp::onPause(); }

    void Dashboard::onStop() { FairWindApp::onStop(); }

    void Dashboard::onDestroy() { FairWindApp::onDestroy(); }

    void Dashboard::onConfigChanged() { FairWindApp::onConfigChanged(); }

    bool Dashboard::onInstall() {
        FairWindApp::onInstall();

        return true;
    }

    bool Dashboard::onUninstall() {
        FairWindApp::onUninstall();

        return true;
    }

    void Dashboard::onStart() {
        FairWindApp::onStart();

        QString route = getRoute();
        if (route.isEmpty()) {
            route = "__home__";
        }

        auto mainPage = new MainPage();

        add(mainPage, route);

        show(route);
    }

    Dashboard::~Dashboard() {
    }
}