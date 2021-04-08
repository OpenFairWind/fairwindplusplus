//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_DASHBOARD_HPP
#define FAIRWIND_DASHBOARD_HPP

#include <QObject>
#include <QtPlugin>
#include <include/FairWindExtension.hpp>

#include "../../../include/IFairWindApp.hpp"


namespace fairwind::extensions::apps::dashboard {
    class Dashboard : public QObject, FairWindExtension, IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::extensions::apps::IFairWindApp)

    public:
        ~Dashboard() = default;

        void init(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;

    private:

    };
}


#endif //FAIRWIND_DASHBOARD_HPP
