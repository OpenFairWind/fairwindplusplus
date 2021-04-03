//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_NATIVE_HPP
#define FAIRWIND_NATIVE_HPP


#include "../../include/IFairWindApp.hpp"
#include "../../include/FairWindApp.hpp"

namespace fairwind::apps::native {
    class Native : public QObject, public FairWindApp, public IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:


        ~Native() override = default;

        QImage getIcon() const override;

    };
}


#endif //FAIRWIND_NATIVE_HPP
