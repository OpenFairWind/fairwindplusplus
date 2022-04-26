//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include "IMSF.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::imsf {

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
    void IMSF::onStart() {
        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);
        show();
    }


    void IMSF::onCreate() { FairWindApp::onCreate(); }

    void IMSF::onResume() { FairWindApp::onResume(); }

    void IMSF::onPause() { FairWindApp::onPause(); }

    void IMSF::onStop() { FairWindApp::onStop(); }

    void IMSF::onDestroy() { FairWindApp::onDestroy(); }

    void IMSF::onConfigChanged() { FairWindApp::onConfigChanged(); }

    bool IMSF::onInstall() { FairWindApp::onInstall(); return true;}

    bool IMSF::onUninstall() { FairWindApp::onUninstall(); return true;}

}

