//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Radar.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::radar {
    void Radar::onCreate() {
        FairWindApp::onCreate();
    }

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
    void Radar::onStart() {
        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);
        show();
    }


    void Radar::onResume() {
        FairWindApp::onResume();
    }

    void Radar::onPause() {
        FairWindApp::onPause();
    }

    void Radar::onStop() {
        FairWindApp::onStop();
    }

    void Radar::onDestroy() {
        FairWindApp::onDestroy();
    }

    void Radar::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }

    bool Radar::onInstall() {
        FairWindApp::onInstall();
        return true;
    }

    bool Radar::onUninstall() {
        FairWindApp::onUninstall();
        return true;
    }
}