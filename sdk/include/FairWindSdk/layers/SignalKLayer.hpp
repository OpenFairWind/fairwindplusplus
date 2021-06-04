//
// Created by Raffaele Montella on 05/05/21.
//

#ifndef FAIRWIND_SIGNALKLAYER_HPP
#define FAIRWIND_SIGNALKLAYER_HPP


#include <FairWindSdk/FairWindSDK.hpp>
#include <FairWindSdk/IFairWindLayer.hpp>
#include <QGeoView/QGVLayer.h>

namespace fairwind::layers {


    class FAIRWINDSDK_LIB_DECL SignalKLayer : public QGVLayer, public fairwind::layers::IFairWindLayer {
    Q_OBJECT
        //Q_INTERFACES(fairwind::layers::IFairWindLayer)

    public:
        explicit SignalKLayer();

        SignalKLayer(const SignalKLayer &other);

        ~SignalKLayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        IFairWindLayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:

    };
}
#endif //FAIRWIND_SIGNALKLAYER_HPP
