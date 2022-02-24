//
// Created by __author__ on 16/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Sonar.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::sonar {
    void Sonar::onCreate() {
        FairWindApp::onCreate();
    }

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
    void Sonar::onStart() {
        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);
        show();
    }

    void Sonar::onResume() {
        FairWindApp::onResume();
    }

    void Sonar::onPause() {
        FairWindApp::onPause();
    }

    void Sonar::onStop() {
        FairWindApp::onStop();
    }

    void Sonar::onDestroy() {
        FairWindApp::onDestroy();
    }

    void Sonar::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }

    void Sonar::onInstall() {
        FairWindApp::onInstall();
    }

    void Sonar::onUninstall() {
        FairWindApp::onUninstall();
    }
}


