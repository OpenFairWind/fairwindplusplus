//
// Created by Raffaele Montella on 21/05/21.
//

#ifndef FAIRWIND_TILEDLAYER_HPP
#define FAIRWIND_TILEDLAYER_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QGeoView/QGVLayerOSM.h>
#include "ILayer.hpp"

namespace fairwind::layers {
    class FAIRWINDSDK_LIB_DECL FairWindTiledLayer : public QGVLayerOSM, public fairwind::layers::ILayer {
    Q_OBJECT

    public:
        explicit FairWindTiledLayer();

        ~FairWindTiledLayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        virtual ILayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:


    };
}


#endif //FAIRWIND_TILEDLAYER_HPP
