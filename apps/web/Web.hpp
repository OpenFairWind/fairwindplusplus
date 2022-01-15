//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_WEB_HPP
#define FAIRWIND_WEB_HPP


#include <FairWindSdk/IFairWindApp.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include <QWebEngineProfile>

namespace fairwind::apps::web {
    class Web : public IFairWindApp {
    Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~Web() = default;

        // App lifecycle
        void onCreate() override;
        void onStart() override;
        void onResume() override;
        void onPause() override;
        void onStop() override;
        void onDestroy() override;

        void updateSettings(QString settingsID, QString newValue) override;

    private:
        QWebEngineProfile *m_profile;

    };
}



#endif //FAIRWIND_WEB_HPP
