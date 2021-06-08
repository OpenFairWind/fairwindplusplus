//
// Created by Raffaele Montella on 21/05/21.
//

#ifndef FAIRWIND_OSMLAYER_HPP
#define FAIRWIND_OSMLAYER_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QGeoView/QGVLayerOSM.h>
#include <FairWindSdk/ILayer.hpp>

namespace fairwind::layers {
    class FAIRWINDSDK_LIB_DECL FairWindOSMLayer : public QGVLayerOSM, public fairwind::layers::ILayer {
    Q_OBJECT

    public:
        explicit FairWindOSMLayer();

        ~FairWindOSMLayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        virtual ILayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:


    };
}


#endif //FAIRWIND_OSMLAYER_HPP
