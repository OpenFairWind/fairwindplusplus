//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_IFAIRWINDAPP_HPP
#define FAIRWIND_IFAIRWINDAPP_HPP

#include <QtPlugin>
#include <QString>
#include <QImage>
#include <QMainWindow>

#define IID_FAIRWIND_APPS "it.uniparthenope.fairwind.apps"

namespace fairwind::extensions::apps {

    class IFairWindApp {
    public:
        virtual ~IFairWindApp() = default;

        virtual void init(QJsonObject *metaData) = 0;


        virtual QString getId() const = 0;
        virtual QString getName() const = 0;
        virtual QString getDesc() const  = 0;


        virtual QImage getIcon() const = 0;
        virtual QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) = 0;
    };

}

Q_DECLARE_INTERFACE(fairwind::extensions::apps::IFairWindApp, IID_FAIRWIND_APPS)



#endif //FAIRWIND_IFAIRWINDAPP_HPP
