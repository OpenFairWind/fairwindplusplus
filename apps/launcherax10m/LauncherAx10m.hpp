//
// Created by __author__ on 21/01/2022.
//

#ifndef LAUNCHERAX10M_HPP
#define LAUNCHERAX10M_HPP

#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/IFairWindLauncher.hpp>


namespace fairwind::apps::launcherax10m {
    class LauncherAx10m : public IFairWindLauncher {
    Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~LauncherAx10m() = default;

        // App lifecycle
        void onCreate() override;
        void onStart() override;
        void onResume() override;
        void onPause() override;
        void onStop() override;
        void onDestroy() override;

    public
        slots:
        void setForegroundApp(QString hash);

    private:

    };
}

#endif //LAUNCHERAX10M_HPP
