//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_DASHBOARD_HPP
#define FAIRWIND_DASHBOARD_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>

namespace fairwind::apps::dashboard {
    class Dashboard : public IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~Dashboard();

        // App lifecycle
        void onCreate() override;
        void onStart() override;
        void onResume() override;
        void onPause() override;
        void onStop() override;
        void onDestroy() override;

        void onConfigChanged() override;

        bool onInstall() override;
        bool onUninstall() override;

    private:
        QJsonObject m_config;
    };
}


#endif //FAIRWIND_DASHBOARD_HPP
