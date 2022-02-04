//
// Created by Raffaele Montella on 11/01/22.
//

#ifndef FAIRWIND_PAGEBASE_HPP
#define FAIRWIND_PAGEBASE_HPP

#include <QJsonObject>
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/FairWindApp.hpp>

namespace fairwind::apps {
    class FAIRWINDSDK_LIB_DECL PageBase: public QWidget {
    Q_OBJECT

    public:
            PageBase(QWidget *parent = nullptr, FairWindApp *fairWindApp = nullptr);
            ~PageBase() = default;

            FairWindApp *getFairWindApp();

        // Called by the app loader when the app is loaded
        virtual void onCreate();

        // Method called when the app is first launched by the user (only one time in the lifecycle)
        virtual void onStart();

        // Called when the app is going to be in foreground
        virtual void onResume();

        // Called when the app is going to be in background
        virtual void onPause();

        // Called when the app is going to be stopped
        virtual void onStop();

        // Called when the app is going to be unloaded by the system
        virtual void onDestroy();

        // Called when the config changed
        virtual void onConfigChanged();

    private:
            apps::FairWindApp *m_fairWindApp;
    };
};


#endif //FAIRWIND_PAGEBASE_HPP
