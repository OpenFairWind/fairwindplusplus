//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef GC1530_HPP
#define GC1530_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <QWebEngineProfile>
#include "WebView.hpp"

namespace it::gov::guardiacostiera::gc1530 {
    class GC1530 : public ::fairwind::apps::IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~GC1530() = default;

        // App lifecycle
        void onCreate() override;
        void onStart() override;
        void onResume() override;
        void onPause() override;
        void onStop() override;
        void onDestroy() override;

        void updateSettings(QString settingsID, QString newValue) override;

        QString getHomeUrl();

    private:
        QWebEngineProfile *m_profile;
        QString m_homeUrl;

    };
}

#endif //GC1530_HPP
