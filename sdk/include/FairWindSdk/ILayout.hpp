//
// Created by Raffaele Montella on 10/06/21.
//

#ifndef FAIRWIND_ILAYOUT_HPP
#define FAIRWIND_ILAYOUT_HPP

#include <FairWindSdk/IDisplay.hpp>

namespace fairwind::layouts {
    /*
     * ILayout
     * Interface to build new visual layouts for FairWind
     */
    class ILayout {
    public:
        virtual ~ILayout() = default;

        // Returns the layout's icon
        virtual QImage getIcon() const = 0;

        // Initialisation method
        virtual void onInit(QMap <QString, QVariant> params) = 0;

        // Returns a newly created instance
        virtual ILayout *getNewInstance() = 0;

        // Method called when the layout's settings are launched by the user
        virtual QWidget *onSettings() = 0;

        // Returns the layout's class name
        virtual QString getClassName() const = 0;

        // Returns the layout in form of Qt widget
        virtual QWidget *getWidget() = 0;

        // Adds a new widget to the layout
        virtual void addDisplay(QString key, displays::IDisplay *display) = 0;
    };
}

#endif //FAIRWIND_ILAYOUT_HPP