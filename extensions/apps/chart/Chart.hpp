//
// Created by Raffaele Montella on 05/04/21.
//

#ifndef FAIRWIND_CHART_HPP
#define FAIRWIND_CHART_HPP


#include <QObject>
#include <QtPlugin>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QGeoView/QGVMap.h>
#include <include/FairWindExtension.hpp>

#include "../../../include/IFairWindApp.hpp"

namespace fairwind::extensions::apps::chart {
    class Chart : public QObject, FairWindExtension, IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::extensions::apps::IFairWindApp)

    public:
        ~Chart() = default;

        void init(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override ;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;

    //private Q_SLOTS:


    private:
        void mapSetup();

        QGVMap *m_widgetMapApp= nullptr;


        QNetworkAccessManager* mManager;
        QNetworkDiskCache* mCache;
    };
}


#endif //FAIRWIND_CHART_HPP
