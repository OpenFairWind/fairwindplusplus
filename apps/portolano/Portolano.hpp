//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef PORTOLANO_HPP
#define PORTOLANO_HPP

#include <QtPlugin>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>

#include <QSqlDatabase>


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

        void onConfigChanged() override;

        void onInstall() override;
        void onUninstall() override;

        QSqlDatabase *getDb();

    private:

        QSqlDatabase mDb;
    };
}

#endif //PORTOLANO_HPP
