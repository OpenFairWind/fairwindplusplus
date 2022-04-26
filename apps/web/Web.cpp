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



namespace fairwind::apps::web {
    void Web::onCreate() {
        FairWindApp::onCreate();

        QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
        QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
        QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif
        m_profile = QWebEngineProfile::defaultProfile();

    }

    void Web::onStart() {
        FairWindApp::onStart();

        QString route = getRoute();
        if (route.isEmpty()) {
            route = "__home__";
        }

        auto mainPage = new MainPage();

        add(mainPage, route);

        show(route);
    }

    void Web::onResume() {
        FairWindApp::onResume();
    }

    void Web::onPause() {
        FairWindApp::onPause();
    }

    void Web::onStop() {
        FairWindApp::onStop();
    }

    void Web::onDestroy() {
        FairWindApp::onDestroy();
    }

    void Web::onConfigChanged() {
        FairWindApp::onConfigChanged();
    }

    bool Web::onInstall() {
        FairWindApp::onInstall();
        return true;
    }

    bool Web::onUninstall() {
        FairWindApp::onUninstall();
        return true;
    }
}
