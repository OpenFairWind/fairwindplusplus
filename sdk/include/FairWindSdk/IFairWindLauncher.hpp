//
// Created by Raffaele Montella on 21/01/22.
//

#ifndef FAIRWIND_IFAIRWINDLAUNCHER_HPP
#define FAIRWIND_IFAIRWINDLAUNCHER_HPP

#include <FairWindSdk/FairWindApp.hpp>
#include <FairWindSdk/IFairWindApp.hpp>

namespace fairwind::apps {
    /*
     * IApp
     * Interface to build FairWind apps
     */
    class IFairWindLauncher : public IFairWindApp {
        Q_OBJECT

    public:
        // ~IApp
        virtual ~IFairWindLauncher() = default;

        signals:

        void foregroundAppChanged(const QString hash);
    };
}
#endif //FAIRWIND_IFAIRWINDLAUNCHER_HPP
