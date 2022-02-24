//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef UAV_HPP
#define UAV_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>


namespace fairwind::apps::uav {
    class UAV : public ::fairwind::apps::IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~UAV() = default;

        // App lifecycle
        void onCreate() override;
        void onStart() override;
        void onResume() override;
        void onPause() override;
        void onStop() override;
        void onDestroy() override;

        void onConfigChanged() override;

        void onInstall() override;
        void onUninstall() override;

    private:
    };
}

#endif //UAV_HPP
