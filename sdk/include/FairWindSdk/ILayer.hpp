//
// Created by Raffaele Montella on 08/05/21.
//

#ifndef FAIRWIND_ILAYER_HPP
#define FAIRWIND_ILAYER_HPP

namespace fairwind::layers {

    class ILayer {
    public:
        virtual ~ILayer() = default;

        virtual QImage getIcon() const = 0;

        virtual void onInit(QMap<QString, QVariant> params) = 0;

        virtual ILayer *getNewInstance()  = 0;

        virtual QWidget *onLegenda() = 0;
        virtual QWidget *onSettings() = 0;

        virtual QString getClassName() const = 0;
    };

}

#endif //FAIRWIND_ILAYER_HPP
