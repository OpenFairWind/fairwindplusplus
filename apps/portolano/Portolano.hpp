//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef PORTOLANO_HPP
#define PORTOLANO_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>


namespace fairwind::apps::portolano {
    class Portolano : public IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~Portolano() = default;

        // App lifecycle
        void onCreate() override;
        void onStart() override;
        void onResume() override;
        void onPause() override;
        void onStop() override;
        void onDestroy() override;


        void updateSettings(QString settingsID, QString newValue) override;

    private:

    };
}

#endif //PORTOLANO_HPP
