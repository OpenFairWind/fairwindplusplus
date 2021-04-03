//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_WEB_HPP
#define FAIRWIND_WEB_HPP

#include "../../include/IFairWindApp.hpp"
#include "../../include/FairWindApp.hpp"

namespace fairwind::apps::web {
    class Web : public QObject, public FairWindApp, public IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:


        ~Web() override = default;

        QImage getIcon() const override;
    };
}



#endif //FAIRWIND_WEB_HPP
