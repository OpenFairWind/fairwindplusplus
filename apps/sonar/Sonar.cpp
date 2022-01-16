//
// Created by __author__ on 16/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Sonar.hpp"
#include "MainPage.hpp"

void fairwind::apps::sonar::Sonar::onCreate() {
    FairWindApp::onCreate();
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::sonar::Sonar::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage();
    add(mainPage);
    show();
}

void fairwind::apps::sonar::Sonar::onResume() {
    FairWindApp::onResume();
}

void fairwind::apps::sonar::Sonar::onPause() {
    FairWindApp::onPause();
}

void fairwind::apps::sonar::Sonar::onStop() {
    FairWindApp::onStop();
}

void fairwind::apps::sonar::Sonar::onDestroy() {
    FairWindApp::onDestroy();
}
