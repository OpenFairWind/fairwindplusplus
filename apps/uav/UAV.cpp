//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "UAV.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::uav {
    void UAV::onCreate() {
        FairWindApp::onCreate();
    }

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
    void UAV::onStart() {
        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);
        show();
    }


    void UAV::onResume() {
        FairWindApp::onResume();
    }

    void UAV::onPause() {
        FairWindApp::onPause();
    }

    void UAV::onStop() {
        FairWindApp::onStop();
    }

    void UAV::onDestroy() {
        FairWindApp::onDestroy();
    }

    void UAV::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }

    bool UAV::onInstall() {
        FairWindApp::onInstall();
        return true;
    }

    bool UAV::onUninstall() {
        FairWindApp::onUninstall();
        return true;
    }
}