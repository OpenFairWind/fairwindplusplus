//
// Created by __author__ on 18/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include "IMSF.hpp"
#include "MainPage.hpp"



/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void fairwind::apps::imsf::IMSF::onStart() {
    FairWindApp::onStart();

    auto mainPage = new MainPage();
    add(mainPage);
    show();
}


void fairwind::apps::imsf::IMSF::onCreate() { FairWindApp::onCreate(); }

void fairwind::apps::imsf::IMSF::onResume() { FairWindApp::onResume(); }

void fairwind::apps::imsf::IMSF::onPause() { FairWindApp::onPause(); }

void fairwind::apps::imsf::IMSF::onStop() { FairWindApp::onStop(); }

void fairwind::apps::imsf::IMSF::onDestroy() { FairWindApp::onDestroy();}

void fairwind::apps::imsf::IMSF::onConfigChanged() {FairWindApp::onConfigChanged();}

