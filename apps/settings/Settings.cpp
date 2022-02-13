//
// Created by __author__ on 18/01/2022.
//

#include <FairWindSdk/settings/FairComboBox.hpp>
#include <FairWindSdk/settings/FairLineEdit.hpp>
#include <FairWindSdk/settings/FairCheckBox.hpp>
#include <FairWindSdk/settings/DisplaysBrowser.hpp>
#include <FairWindSdk/settings/LayersBrowser.hpp>
#include "Settings.hpp"
#include "MainPage.hpp"
#include "general/General.hpp"
#include "extensions/Extensions.hpp"


namespace fairwind::apps::settings {
    // Called when the app is loaded
    void Settings::onCreate() {

        // Call the framework onCreate()
        FairWindApp::onCreate();

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();

        // Register settings pages inside the FairWind singleton
        fairWind->registerSettingsTab(new general::General());
        //fairWind->registerSettingsTab(new Connections());
        fairWind->registerSettingsTab(new extensions::Extensions());


    }

    //Called by the FairWind framework when the app is invoked for the first time
    void Settings::onStart() {

        // Call the framework onCreate()
        FairWindApp::onStart();

        // Create the main page
        auto mainPage = new MainPage();

        // Add the main page to the app pages as root page
        add(mainPage);

        // Show the root page
        show();
    }

    // Called when the app is going to be in foreground
    void Settings::onResume() {

        // Call the framework onResume()
        FairWindApp::onResume();
    }

    // Called when the app is going to be in background
    void Settings::onPause() {

        // Call the framework onPause()
        FairWindApp::onPause();
    }

    // Called when the app is going to be stopped
    void Settings::onStop() {

        // Call the framework on onStop()
        FairWindApp::onStop();
    }

    // Called when the app is going to be unloaded once and forever
    void Settings::onDestroy() {

        // Call the framework onDestroy()
        FairWindApp::onDestroy();
    }

    // Called when the app is going to be unloaded once and forever
    void Settings::onConfigChanged() {

        // Call the framework onDestroy()
        FairWindApp::onConfigChanged();
    }
} // fairwind::apps::settings