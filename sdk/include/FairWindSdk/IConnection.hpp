//
// Created by Raffaele Montella on 03/06/21.
//

#ifndef FAIRWIND_ICONNECTION_HPP
#define FAIRWIND_ICONNECTION_HPP

namespace fairwind::connections {

    class IConnection {
    public:
        virtual ~IConnection() = default;

        virtual QImage getIcon() const = 0;

        virtual void onInit(QMap<QString, QVariant> params) = 0;

        virtual IConnection *getNewInstance()  = 0;

        virtual QWidget *onSettings() = 0;

        virtual QString getClassName() const = 0;

        virtual void setActive(bool active) = 0;
        virtual bool isActive() const = 0;

        virtual QString getName() const = 0;

        virtual void setLabel(QString label) = 0;
        virtual QString getLabel() const = 0;

    };

}

#endif //FAIRWIND_ICONNECTION_HPP
