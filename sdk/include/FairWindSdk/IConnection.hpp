//
// Created by Raffaele Montella on 03/06/21.
//

#ifndef FAIRWIND_ICONNECTION_HPP
#define FAIRWIND_ICONNECTION_HPP

namespace fairwind::connections {
    /*
     * IConnection
     * Interface to build new connection services for FairWind
     */
    class IConnection {
    public:
        virtual ~IConnection() = default;

        // Returns the connection's icon
        virtual QImage getIcon() const = 0;

        // Initialisation method
        virtual void onInit(QMap <QString, QVariant> params) = 0;

        // Returns a newly created instance
        virtual IConnection *getNewInstance() = 0;

        // Method called when the connection's settings are launched by the user
        virtual QWidget *onSettings() = 0;

        // Returns the connection's class name
        virtual QString getClassName() const = 0;

        // Activate or deactivate the connection
        virtual void setActive(bool active) = 0;

        // Checks if the connections is active
        virtual bool isActive() const = 0;

        // Returns the connection's name
        virtual QString getName() const = 0;

        // Sets the connection's label
        virtual void setLabel(QString label) = 0;

        // Returns the connection's label
        virtual QString getLabel() const = 0;
    };
}

#endif //FAIRWIND_ICONNECTION_HPP