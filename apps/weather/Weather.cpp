//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Weather.hpp"
#include "MainPage.hpp"

void fairwind::apps::weather::Weather::onCreate() {
    FairWindApp::onCreate();
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::weather::Weather::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage();
    add(mainPage);
    show();

}

void fairwind::apps::weather::Weather::onResume() {
    FairWindApp::onResume();
}

void fairwind::apps::weather::Weather::onPause() {
    FairWindApp::onPause();
}

void fairwind::apps::weather::Weather::onStop() {
    FairWindApp::onStop();
}

void fairwind::apps::weather::Weather::onDestroy() {
    FairWindApp::onDestroy();
}