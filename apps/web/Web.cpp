//
// Created by Raffaele Montella on 01/04/21.
//

#include "Web.hpp"
#include "WebView.hpp"
#include "MainPage.hpp"

#include <QWebEngineSettings>
#include <QWebEngineProfile>

#include <QDebug>
#include <QPushButton>
#include <QAbstractButton>
#include <QHBoxLayout>
#include <FairWindSdk/FairWind.hpp>




void fairwind::apps::web::Web::onCreate() {
    FairWindApp::onCreate();

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif
    m_profile = QWebEngineProfile::defaultProfile();

}

void fairwind::apps::web::Web::onStart() {
    FairWindApp::onStart();

    QString route = getRoute();
    if (route.isEmpty()) {
        route = "__home__";
    }

    auto mainPage = new MainPage();

    add(mainPage,route);

    show(route);
}

void fairwind::apps::web::Web::onResume() {
    FairWindApp::onResume();
}

void fairwind::apps::web::Web::onPause() {
    FairWindApp::onPause();
}

void fairwind::apps::web::Web::onStop() {
    FairWindApp::onStop();
}

void fairwind::apps::web::Web::onDestroy() {
    FairWindApp::onDestroy();
}

void fairwind::apps::web::Web::onConfigChanged() {
    FairWindApp::onConfigChanged();
}