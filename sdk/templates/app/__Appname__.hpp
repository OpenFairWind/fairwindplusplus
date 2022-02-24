//
// Created by __author__ on __date__.
//

#ifndef __APPNAME___HPP
#define __APPNAME___HPP

#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>


namespace __namespace__ {
    class __Appname__ : public fairwind::apps::IFairWindApp {
    Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~__Appname__() = default;

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

#endif //__APPNAME___HPP
