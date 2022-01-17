//
// Created by __author__ on 16/07/2021.
//

#include "Portolano.hpp"
#include "MainPage.hpp"


void fairwind::apps::portolano::Portolano::onCreate() {
    FairWindApp::onCreate();
}
/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::portolano::Portolano::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage();
    add(mainPage);
    show();
}

void fairwind::apps::portolano::Portolano::onResume() {
    FairWindApp::onResume();
}

void fairwind::apps::portolano::Portolano::onPause() {
    FairWindApp::onPause();
}

void fairwind::apps::portolano::Portolano::onStop() {
    FairWindApp::onStop();
}

void fairwind::apps::portolano::Portolano::onDestroy() {
    FairWindApp::onDestroy();
}
