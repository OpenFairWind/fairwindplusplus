//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_FAIRWINDAPP_HPP
#define FAIRWIND_FAIRWINDAPP_HPP


#include <QObject>
#include <QJsonDocument>
#include "IFairWindApp.hpp"

namespace fairwind {
    namespace apps {

        class FairWindApp {
        public:

            QSharedPointer<QJsonDocument> getSettings();

        private:
            QJsonDocument settings;
        };
    }
}

#endif //FAIRWIND_FAIRWINDAPP_HPP
