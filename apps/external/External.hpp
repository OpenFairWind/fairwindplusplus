//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_EXTERNAL_HPP
#define FAIRWIND_EXTERNAL_HPP

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>

namespace fairwind::apps::external {
    class External : public IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~External() = default;

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


#endif //FAIRWIND_EXTERNAL_HPP
