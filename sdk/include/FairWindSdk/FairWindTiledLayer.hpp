//
// Created by Raffaele Montella on 21/05/21.
//

#ifndef FAIRWIND_FAIRWINDTILEDLAYER_HPP
#define FAIRWIND_FAIRWINDTILEDLAYER_HPP


#include <QGeoView/QGVLayerOSM.h>
#include "IFairWindLayer.hpp"

class FairWindTiledLayer : public QGVLayerOSM, public fairwind::layers::IFairWindLayer {
Q_OBJECT

public:
    explicit FairWindTiledLayer();
    ~FairWindTiledLayer();

    QImage getIcon() const override;

    void onInit(QMap<QString, QVariant> params) override;

    virtual IFairWindLayer *getNewInstance() override;

    QWidget *onLegenda() override;
    QWidget *onSettings() override;

private:


};


#endif //FAIRWIND_FAIRWINDTILEDLAYER_HPP
