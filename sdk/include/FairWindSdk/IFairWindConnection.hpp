//
// Created by Raffaele Montella on 03/06/21.
//

#ifndef FAIRWIND_IFAIRWINDCONNECTION_HPP
#define FAIRWIND_IFAIRWINDCONNECTION_HPP

namespace fairwind::connections {

    class IFairWindConnection {
    public:
        virtual ~IFairWindConnection() = default;

        virtual QImage getIcon() const = 0;

        virtual void onInit(QMap<QString, QVariant> params) = 0;

        virtual IFairWindConnection *getNewInstance()  = 0;

        virtual QWidget *onSettings() = 0;

        virtual QString getClassName() const = 0;

        virtual void setActive(bool active) = 0;
        virtual bool isActive() const = 0;

    };

}

#endif //FAIRWIND_IFAIRWINDCONNECTION_HPP
