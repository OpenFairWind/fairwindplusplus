//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "UAV.hpp"
#include "MainPage.hpp"


void fairwind::apps::uav::UAV::onCreate() {
    FairWindApp::onCreate();
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::uav::UAV::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage();
    add(mainPage);
    show();}


void fairwind::apps::uav::UAV::onResume() {
    FairWindApp::onResume();
}

void fairwind::apps::uav::UAV::onPause() {
    FairWindApp::onPause();
}

void fairwind::apps::uav::UAV::onStop() {
    FairWindApp::onStop();
}

void fairwind::apps::uav::UAV::onDestroy() {
    FairWindApp::onDestroy();
}

void fairwind::apps::uav::UAV::onConfigChanged() {
    FairWindApp::onConfigChanged();
}