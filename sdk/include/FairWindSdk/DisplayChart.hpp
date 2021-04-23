//
// Created by Raffaele Montella on 22/04/21.
//

#ifndef FAIRWIND_DISPLAYCHART_HPP
#define FAIRWIND_DISPLAYCHART_HPP


#include <QWidget>
#include <QNetworkDiskCache>
#include <QGeoView/QGVImage.h>

namespace Ui {
    class DisplayChart;
}

class DisplayChart: public QWidget {
Q_OBJECT

public:
    explicit DisplayChart(QWidget *parent=0);
    ~DisplayChart();


public slots:
    void mapSetup();
    void updateNavigationPosition();

private:
    Ui::DisplayChart *ui;

    QGVMap *m_widgetMap= nullptr;


    QNetworkAccessManager* mManager;
    QNetworkDiskCache* mCache;

    QGVImage *m_self;
};


#endif //FAIRWIND_DISPLAYCHART_HPP
