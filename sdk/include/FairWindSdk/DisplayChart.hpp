//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYCHART_HPP
#define FAIRWIND_DISPLAYCHART_HPP


#include <QWidget>
#include <QNetworkDiskCache>

#include "QGeoView/QGVLayer.h"

#include "FairWindSDK.hpp"

namespace Ui {
    class DisplayChart;
}

class FAIRWINDSDK_LIB_DECL DisplayChart: public QWidget {
Q_OBJECT

public:
    explicit DisplayChart(QWidget *parent=0);
    ~DisplayChart();


public slots:
    void onInit(QJsonObject settings);
    void updateNavigationPosition(const QJsonObject update);

private:
    Ui::DisplayChart *ui;

    QGVMap *m_widgetMap= nullptr;


    QNetworkAccessManager* mManager;
    QNetworkDiskCache* mCache;

    QJsonObject mSettings;
};


#endif //FAIRWIND_DISPLAYCHART_HPP
