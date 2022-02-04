//
// Created by __author__ on __date__.
//

#include "__Appname__.hpp"
#include "MainPage.hpp"

namespace __namespace__ {
    // Called when the app is loaded
    void __Appname__::onCreate() {

        // Call the framework onCreate()
        FairWindApp::onCreate();
    }

    //Called by the FairWind framework when the app is invoked for the first time
    void __Appname__::onStart() {

        // Call the framework onCreate()
        FairWindApp::onStart();

        // Create the main page
        auto mainPage = new MainPage(nullptr, this);

        // Add the main page to the app pages as root page
        add(mainPage);

        // Show the root page
        show();
    }

    // Called when the app is going to be in foreground
    void __Appname__::onResume() {

        // Call the framework onResume()
        FairWindApp::onResume();
    }

    // Called when the app is going to be in background
    void __Appname__::onPause() {

        // Call the framework onPause()
        FairWindApp::onPause();
    }

    // Called when the app is going to be stopped
    void __Appname__::onStop() {

        // Call the framework on onStop()
        FairWindApp::onStop();
    }

    // Called when the app is going to be unloaded once and forever
    void __Appname__::onDestroy() {

        // Call the framework onDestroy()
        FairWindApp::onDestroy();
    }

    // Called when the configuration file changed
    void __Appname__::onConfigChanged() {

        // Call the framework onConfigChanged()
        FairWindApp::onConfigChanged();
    }

} // __namespace__