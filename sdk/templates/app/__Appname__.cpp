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

        // ToDo: add your code here:
    }

    //Called by the FairWind framework when the app is invoked for the first time
    void __Appname__::onStart() {

        // Call the framework onCreate()
        FairWindApp::onStart();

        // ToDo: add your code here:

        // Create the main page
        auto mainPage = new MainPage();

        // Add the main page to the app pages as root page
        add(mainPage);

        // Show the root page
        show();
    }

    // Called when the app is going to be in foreground
    void __Appname__::onResume() {

        // Call the framework onResume()
        FairWindApp::onResume();

        // ToDo: add your code here:
    }

    // Called when the app is going to be in background
    void __Appname__::onPause() {
        // ToDo: add your code here:

        // Call the framework onPause()
        FairWindApp::onPause();
    }

    // Called when the app is going to be stopped
    void __Appname__::onStop() {
        // ToDo: add your code here:

        // Call the framework on onStop()
        FairWindApp::onStop();
    }

    // Called when the app is going to be unloaded once and forever
    void __Appname__::onDestroy() {
        // ToDo: add your code here:

        // Call the framework onDestroy()
        FairWindApp::onDestroy();
    }

    // Called when the configuration file changed
    void __Appname__::onConfigChanged() {

        // Call the framework onConfigChanged()
        FairWindApp::onConfigChanged();

        // ToDo: add your code here:
    }

    // Called when the app runs the very first time
    bool __Appname__::onInstall() {
        // Define the result value as false by default
        bool result = false;

        // Call the framework onInstall()
        FairWindApp::onInstall();


        // ToDo: add your code here:

        // Return the result to the caller
        return result;
    }

    // Called when the configuration file changed
    bool __Appname__::onUninstall() {
        // Define the result value as false by default
        bool result = false;

        // ToDo: add you code here:


        // Call the framework onUnistall()
        FairWindApp::onUninstall();

        return result;
    }

} // __namespace__