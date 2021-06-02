//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYCHART_HPP
#define FAIRWIND_DISPLAYCHART_HPP


#include <QWidget>
#include <QNetworkDiskCache>

#include "QGeoView/QGVLayer.h"
#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IFairWindDisplay.hpp>

namespace Ui {
    class DisplayChart;
}

class FAIRWINDSDK_LIB_DECL DisplayChart: public QWidget, public fairwind::displays::IFairWindDisplay {
Q_OBJECT

public:
    explicit DisplayChart(QWidget *parent=0);
    ~DisplayChart();

    QString getClassName() const override;
    QImage getIcon() const override;
    void onInit(QMap<QString, QVariant> params) override;
    IFairWindDisplay *getNewInstance()  override;
    QWidget *onSettings() override;
    bool smaller() override;
    bool bigger() override;


public slots:
    //void onInit(QJsonObject settings);
    void updateNavigationPosition(const QJsonObject update);

private:
    Ui::DisplayChart *ui;

    QGVMap *m_widgetMap= nullptr;


    QNetworkAccessManager* mManager;
    QNetworkDiskCache* mCache;

    QJsonObject mSettings;
};


#endif //FAIRWIND_DISPLAYCHART_HPP
