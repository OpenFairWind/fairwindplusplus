//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Weather.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::weather {
    void Weather::onCreate() {
        FairWindApp::onCreate();
    }

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
    void Weather::onStart() {
        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);
        show();

    }

    void Weather::onResume() {
        FairWindApp::onResume();
    }

    void Weather::onPause() {
        FairWindApp::onPause();
    }

    void Weather::onStop() {
        FairWindApp::onStop();
    }

    void Weather::onDestroy() {
        FairWindApp::onDestroy();
    }

    void Weather::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }

    void Weather::onInstall() {
        FairWindApp::onUninstall();
    }
}