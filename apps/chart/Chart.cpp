//
// Created by Raffaele Montella on 05/04/21.
//

#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <QLabel>
#include <QFile>
#include <FairWindSdk/IDisplay.hpp>
#include <FairWindSdk/displays/DisplayChart.hpp>
#include "Chart.hpp"
#include "MainPage.hpp"

namespace fairwind::apps::chart {


    // Called by the FairWind framework when the app is invoked for the first time
    void Chart::onStart() {

        FairWindApp::onStart();

        auto mainPage = new MainPage();
        add(mainPage);

        show();
    }

    void Chart::onCreate() {
        FairWindApp::onCreate();

    }

    void Chart::onResume() {
        FairWindApp::onResume();
    }

    void Chart::onPause() {
        FairWindApp::onPause();
    }

    void Chart::onStop() {
        FairWindApp::onStop();
    }

    void Chart::onDestroy() {
        FairWindApp::onDestroy();
    }

    void Chart::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }
}