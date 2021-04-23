//
// Created by Raffaele Montella on 05/04/21.
//

#ifndef FAIRWIND_CHART_HPP
#define FAIRWIND_CHART_HPP


#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/FairWindAppBase.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include "FairWindSdk/DisplayChart.hpp"


namespace fairwind::apps::chart {
    class Chart : public QObject, FairWindAppBase, IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~Chart() = default;

        void onInit(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override ;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;
        QWidget *onSettings(QTabWidget *tabWidgets) override;




    private:
        QWidget *m_widget = nullptr;
    };
}


#endif //FAIRWIND_CHART_HPP
