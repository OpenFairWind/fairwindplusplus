//
// Created by Raffaele Montella on 08/05/21.
//

#ifndef FAIRWIND_IFAIRWINDLAYER_HPP
#define FAIRWIND_IFAIRWINDLAYER_HPP

//#define IID_FAIRWIND_LAYERS "it.uniparthenope.fairwind.layers"

namespace fairwind::layers {

    class IFairWindLayer {
    public:
        virtual ~IFairWindLayer() = default;

        virtual QImage getIcon() const = 0;

        virtual void onInit(QMap<QString, QVariant> params) = 0;

        virtual IFairWindLayer *getNewInstance()  = 0;

        virtual QWidget *onLegenda() = 0;
        virtual QWidget *onSettings() = 0;

        virtual QString getClassName() const = 0;
    };

}

//Q_DECLARE_INTERFACE(fairwind::layers::IFairWindLayer, IID_FAIRWIND_LAYERS)
#endif //FAIRWIND_IFAIRWINDLAYER_HPP
