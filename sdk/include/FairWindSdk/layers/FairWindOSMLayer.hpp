//
// Created by Raffaele Montella on 21/05/21.
//

#ifndef FAIRWIND_FAIRWINDOSMLAYER_HPP
#define FAIRWIND_FAIRWINDOSMLAYER_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QGeoView/QGVLayerOSM.h>
#include <FairWindSdk/IFairWindLayer.hpp>

namespace fairwind::layers {
    class FAIRWINDSDK_LIB_DECL FairWindOSMLayer : public QGVLayerOSM, public fairwind::layers::IFairWindLayer {
    Q_OBJECT

    public:
        explicit FairWindOSMLayer();

        ~FairWindOSMLayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        virtual IFairWindLayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:


    };
}


#endif //FAIRWIND_FAIRWINDOSMLAYER_HPP
