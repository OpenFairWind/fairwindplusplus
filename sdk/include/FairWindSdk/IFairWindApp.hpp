//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_IFAIRWINDAPP_HPP
#define FAIRWIND_IFAIRWINDAPP_HPP

#include <QtPlugin>
#include <QString>
#include <QImage>
#include <QMainWindow>
#include <FairWindSdk/FairWindApp.hpp>

#define IID_FAIRWIND_APPS "it.uniparthenope.fairwind.apps"

namespace fairwind::apps {
    /*
     * IApp
     * Interface to build FairWind apps
     */
    class IFairWindApp: public FairWindApp {
    public:
        // ~IApp
        virtual ~IFairWindApp() = default;

        // Initialisation method
        virtual void onCreate() = 0;

        // Method called when the app is first launched by the user (only one time in the lifecycle)
        virtual void onStart() = 0;

        // Called when the application is going in foreground
        virtual void onResume() = 0;

        // Called when the application is going in background
        virtual void onPause() = 0;

        // Called when the application is going to be stopped (only one time in the lifecycle)
        virtual void onStop() = 0;

        // Finalization method
        virtual void onDestroy() = 0;

        // Called when settings are set
        virtual void onConfigChanged() = 0;

        // Called when the app runs the first time ever
        virtual void onInstall() = 0;

        // Called when the app runs its last time
        virtual void onUninstall() = 0;
    };
}

Q_DECLARE_INTERFACE(fairwind::apps::IFairWindApp,
IID_FAIRWIND_APPS)

#endif //FAIRWIND_IFAIRWINDAPP_HPP