//
// Created by Raffaele Montella on 10/06/21.
//

#ifndef FAIRWIND_ILAYOUT_HPP
#define FAIRWIND_ILAYOUT_HPP

#include <FairWindSdk/IDisplay.hpp>

namespace fairwind::layouts {

    class ILayout {
    public:
        virtual ~ILayout() = default;

        virtual QImage getIcon() const = 0;
        virtual void onInit(QMap<QString, QVariant> params) = 0;
        virtual ILayout *getNewInstance()  = 0;
        virtual QWidget *onSettings() = 0;
        virtual QString getClassName() const = 0;

        virtual QWidget *getWidget() = 0;
        virtual void addDisplay(QString key, displays::IDisplay *display) = 0;
    };

}

#endif //FAIRWIND_ILAYOUT_HPP
