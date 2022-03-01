//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Video.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::video {
    void Video::onCreate() {
        FairWindApp::onCreate();
    }

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
    void Video::onStart() {
        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);
        show();
    }

    void Video::onResume() {
        FairWindApp::onResume();
    }

    void Video::onPause() {
        FairWindApp::onPause();
    }

    void Video::onStop() {
        FairWindApp::onStop();
    }

    void Video::onDestroy() {
        FairWindApp::onDestroy();
    }

    void Video::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }

    bool Video::onInstall() {
        FairWindApp::onInstall();
        return true;
    }

    bool Video::onUninstall() {
        FairWindApp::onUninstall();
        return true;
    }
}