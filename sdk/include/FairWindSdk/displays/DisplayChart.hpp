//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYCHART_HPP
#define FAIRWIND_DISPLAYCHART_HPP

#include <QWidget>
#include <QNetworkDiskCache>

#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IDisplay.hpp>
#include <QNetworkAccessManager>

#include <QGeoView/QGVMap.h>

namespace Ui {
    class DisplayChart;
}

namespace fairwind::displays {
    /*
     * DisplayChart
     * A visual display component that emulates the functionalities fo a chart, providing different data at once
     */
    class FAIRWINDSDK_LIB_DECL DisplayChart : public QWidget, public fairwind::displays::IDisplay {
    Q_OBJECT
    public:
        explicit DisplayChart(QWidget *parent = 0);
        ~DisplayChart();

        // IDisplay methods
        QString getClassName() const override;
        QImage getIcon() const override;
        void onInit(QMap<QString, QVariant> params) override;
        IDisplay *getNewInstance() override;
        QWidget *onSettings() override;


    public slots:
        void updateNavigationPosition(const QJsonObject& update);
        void updateNavigationCourseOverGroundTrue(const QJsonObject& update);
        void updateNavigationSpeedOverGround(const QJsonObject& update);

    private:
        Ui::DisplayChart *ui;

        QGVMap *m_widgetMap = nullptr;

        QNetworkAccessManager *mManager;
        QNetworkDiskCache *mCache;

        QJsonObject mConfig;
    };
}

#endif //FAIRWIND_DISPLAYCHART_HPP