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
            PageBase(QWidget *parent = nullptr);
            ~PageBase() = default;


            FairWindApp *getFairWindApp();

        void setFairWindApp(FairWindApp *pApp);

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

        // Called when a page is going to be shown using the FairWindApp::show(...) method
        virtual void onShowing();

        // Called when a page is shown using the FairWindApp::show(...) method
        virtual void onShown();

        // Called when a page is going to be added using the FairWindApp::add(...) method
        virtual void onAdding();

        // Called when a page is added using the FairWindApp::add(...) method
        virtual void onAdded();

        // Called when a page is going to be removed using the FairWindApp::remove(...) method
        virtual void onRemoving();

        // Called when a page is removed using the FairWindApp::remove(...) method
        virtual void onRemoved();



    private:
            apps::FairWindApp *m_fairWindApp;
    };
};


#endif //FAIRWIND_PAGEBASE_HPP
