//
// Created by Raffaele Montella on 08/05/21.
//

#ifndef FAIRWIND_ILAYER_HPP
#define FAIRWIND_ILAYER_HPP

namespace fairwind::layers {
    /*
     * ILayer
     * Interface to create new layer widgets for FairWind
     */
    class ILayer {
    public:
        virtual ~ILayer() = default;

        // Returns the layer's icon
        virtual QImage getIcon() const = 0;

        // Initialisation method
        virtual void onInit(QMap <QString, QVariant> params) = 0;

        // Returns a newly created instance
        virtual ILayer *getNewInstance() = 0;

        // Method called when the layer's legenda needs to be raised
        virtual QWidget *onLegenda() = 0;

        // Method called when the layer's settings are launched by the user
        virtual QWidget *onSettings() = 0;

        // Returns the layer's class name
        virtual QString getClassName() const = 0;
    };
}

#endif //FAIRWIND_ILAYER_HPP