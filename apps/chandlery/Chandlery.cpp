//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "Chandlery.hpp"
#include "MainPage.hpp"



// Called by the FairWind framework when the app is invoked for the first time
void fairwind::apps::chandlery::Chandlery::onStart() {
    // Invoke the AppBase implementation

    FairWindApp::onStart();

    MainPage *mainPage = new MainPage(nullptr, this);
    FairWindApp::add(mainPage);
    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = FairWindApp::getConfig();
    FairWindApp::show();
}

void fairwind::apps::chandlery::Chandlery::onCreate() {
    FairWindApp::onCreate();
}

void fairwind::apps::chandlery::Chandlery::onResume()  {
    FairWindApp::onResume();
}

void fairwind::apps::chandlery::Chandlery::onPause()  {
    FairWindApp::onPause();
}

void fairwind::apps::chandlery::Chandlery::onStop()  {
    FairWindApp::onStop();
}

void fairwind::apps::chandlery::Chandlery::onDestroy()  {
    FairWindApp::onDestroy();
}

void fairwind::apps::chandlery::Chandlery::onConfigChanged()  {
    FairWindApp::onConfigChanged();
}

