//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_IFAIRWINDAPP_HPP
#define FAIRWIND_IFAIRWINDAPP_HPP

#include <QtPlugin>
#include <QString>
#include <QImage>

#define IID_FAIRWIND_APPS "it.uniparthenope.fairwind.apps"

namespace fairwind {
    namespace apps {

        class IFairWindApp {
        public:
            virtual ~IFairWindApp() {};

            virtual QImage getIcon() const = 0;

        };

    }
}

Q_DECLARE_INTERFACE(fairwind::apps::IFairWindApp, IID_FAIRWIND_APPS)



#endif //FAIRWIND_IFAIRWINDAPP_HPP
