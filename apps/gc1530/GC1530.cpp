//
// Created by __author__ on 16/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include <QWebEngineSettings>
#include <QWebEngineProfile>

#include "GC1530.hpp"
#include "MainPage.hpp"


/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
void it::gov::guardiacostiera::gc1530::GC1530::onStart() {

    FairWindApp::onStart();

    // Set the home URL
    m_homeUrl="https://www.guardiacostiera.gov.it";

    auto mainPage = new MainPage();
    FairWindApp::add(mainPage);

    FairWindApp::show();

    show();
}

void it::gov::guardiacostiera::gc1530::GC1530::onCreate() {
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif
    m_profile = QWebEngineProfile::defaultProfile();

}

void it::gov::guardiacostiera::gc1530::GC1530::onResume() { fairwind::apps::FairWindApp::onResume();}
void it::gov::guardiacostiera::gc1530::GC1530::onPause() { fairwind::apps::FairWindApp::onPause();}
void it::gov::guardiacostiera::gc1530::GC1530::onStop() {fairwind::apps::FairWindApp::onStop();}
void it::gov::guardiacostiera::gc1530::GC1530::onDestroy() {fairwind::apps::FairWindApp::onDestroy();}
void it::gov::guardiacostiera::gc1530::GC1530::onConfigChanged() {fairwind::apps::FairWindApp::onConfigChanged();}

QString it::gov::guardiacostiera::gc1530::GC1530::getHomeUrl() {
    return m_homeUrl;
}
