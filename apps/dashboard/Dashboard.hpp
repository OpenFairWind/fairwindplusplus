//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_DASHBOARD_HPP
#define FAIRWIND_DASHBOARD_HPP

#include <QObject>
#include <QtPlugin>

#include "../../include/IFairWindApp.hpp"
#include "../../include/FairWindApp.hpp"

namespace fairwind::apps::dashboard {
    class Dashboard : public QObject, public FairWindApp, public IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~Dashboard() override = default;

        QImage getIcon() const override;

    };
}


#endif //FAIRWIND_DASHBOARD_HPP
