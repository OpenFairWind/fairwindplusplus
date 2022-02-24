//
// Created by __author__ on 21/01/2022.
//

#include "LauncherAx10m.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::launcherax10m {
    // Called when the app is loaded
    void LauncherAx10m::onCreate() {

        // Call the framework onCreate()
        FairWindApp::onCreate();
    }

    //Called by the FairWind framework when the app is invoked for the first time
    void LauncherAx10m::onStart() {

        // Call the framework onCreate()
        FairWindApp::onStart();

        // Create the main page
        auto mainPage = new MainPage();

        connect(mainPage,&MainPage::foregroundAppChanged,this,&LauncherAx10m::setForegroundApp);

        // Add the main page to the app pages as root page
        add(mainPage);

        // Show the root page
        show();
    }

    void LauncherAx10m::setForegroundApp(QString hash)  {
        emit foregroundAppChanged(hash);
    }

    // Called when the app is going to be in foreground
    void LauncherAx10m::onResume() {

        // Call the framework onResume()
        FairWindApp::onResume();
    }

    // Called when the app is going to be in background
    void LauncherAx10m::onPause() {

        // Call the framework onPause()
        FairWindApp::onPause();
    }

    // Called when the app is going to be stopped
    void LauncherAx10m::onStop() {

        // Call the framework on onStop()
        FairWindApp::onStop();
    }

    // Called when the app is going to be unloaded once and forever
    void LauncherAx10m::onDestroy() {

        // Call the framework onDestroy()
        FairWindApp::onDestroy();
    }

    // Called the config changed
    void LauncherAx10m::onConfigChanged() {

        // Call the framework onDestroy()
        FairWindApp::onConfigChanged();
    }

    void LauncherAx10m::onInstall() {

        // Call the framework onDestroy()
        FairWindApp::onInstall();
    }

    void LauncherAx10m::onUninstall() {

        // Call the framework onDestroy()
        FairWindApp::onUninstall();
    }

} // fairwind::apps::launcherax10m