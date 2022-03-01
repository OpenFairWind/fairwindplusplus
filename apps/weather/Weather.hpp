//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef WEATHER_HPP
#define WEATHER_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>


namespace fairwind::apps::weather {
    class Weather : public ::fairwind::apps::IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~Weather() = default;

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

    };
}

#endif //WEATHER_HPP
