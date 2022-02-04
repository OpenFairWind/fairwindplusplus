//
// Created by Raffaele Montella on 15/07/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QMessageBox>
#include "Entertainment.hpp"
#include "MainPage.hpp"


/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::entertainment::Entertainment::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage(nullptr, this);
    add(mainPage);
    show();
}

void fairwind::apps::entertainment::Entertainment::onCreate() { FairWindApp::onCreate();}

void fairwind::apps::entertainment::Entertainment::onResume() { FairWindApp::onResume();}

void fairwind::apps::entertainment::Entertainment::onPause() { FairWindApp::onPause();}

void fairwind::apps::entertainment::Entertainment::onStop() { FairWindApp::onStop();}

void fairwind::apps::entertainment::Entertainment::onDestroy() { FairWindApp::onDestroy();}

void fairwind::apps::entertainment::Entertainment::onConfigChanged() { FairWindApp::onConfigChanged();}