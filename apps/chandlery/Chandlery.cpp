//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Chandlery.hpp"
#include "MainPage.hpp"


namespace fairwind::apps::chandlery {
    
    // Called by the FairWind framework when the app is invoked for the first time
    void Chandlery::onStart() {
        // Invoke the AppBase implementation

        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);

        show();
    }

    void Chandlery::onCreate() {
        FairWindApp::onCreate();
    }

    void Chandlery::onResume() {
        FairWindApp::onResume();
    }

    void Chandlery::onPause() {
        FairWindApp::onPause();
    }

    void Chandlery::onStop() {
        FairWindApp::onStop();
    }

    void Chandlery::onDestroy() {
        FairWindApp::onDestroy();
    }

    void Chandlery::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }

    bool Chandlery::onInstall() {
        FairWindApp::onInstall();
        return true;
    }

    bool Chandlery::onUninstall() {
        FairWindApp::onUninstall();
        return true;
    }

}