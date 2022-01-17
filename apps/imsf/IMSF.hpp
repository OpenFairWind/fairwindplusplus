//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef IMSF_HPP
#define IMSF_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include "MainPage.hpp"

namespace fairwind::apps::imsf {
    class IMSF :public IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~IMSF() = default;

        // App lifecycle
        void onCreate() override;
        void onStart() override;
        void onResume() override;
        void onPause() override;
        void onStop() override;
        void onDestroy() override;

    private:


    };
}

#endif //IMSF_HPP
