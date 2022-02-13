//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Video.hpp"
#include "MainPage.hpp"


void fairwind::apps::video::Video::onCreate() {
    FairWindApp::onCreate();
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::video::Video::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage();
    add(mainPage);
    show();
}

void fairwind::apps::video::Video::onResume() {
    FairWindApp::onResume();
}

void fairwind::apps::video::Video::onPause() {
    FairWindApp::onPause();
}

void fairwind::apps::video::Video::onStop() {
    FairWindApp::onStop();
}

void fairwind::apps::video::Video::onDestroy() {
    FairWindApp::onDestroy();
}

void fairwind::apps::video::Video::onConfigChanged() {
    FairWindApp::onConfigChanged();
}