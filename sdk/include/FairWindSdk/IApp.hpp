//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_IAPP_HPP
#define FAIRWIND_IAPP_HPP

#include <QtPlugin>
#include <QString>
#include <QImage>
#include <QMainWindow>

#define IID_FAIRWIND_APPS "it.uniparthenope.fairwind.apps"

namespace fairwind::apps {

    class IApp {
    public:
        virtual ~IApp() = default;

        virtual void onInit(QJsonObject *metaData) = 0;


        virtual QString getId() const = 0;
        virtual QString getName() const = 0;
        virtual QString getDesc() const  = 0;
        virtual QString getVersion() const  = 0;
        virtual QString getVendor() const  = 0;
        virtual QString getCopyright() const  = 0;
        virtual QString getLicense() const  = 0;

        virtual QImage getIcon() const = 0;
        virtual QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) = 0;
        virtual QWidget *onSettings(QTabWidget *tabWidget) = 0;
        virtual QJsonObject getConfig() = 0;
        virtual QJsonObject getMetaData() = 0;
    };

}

Q_DECLARE_INTERFACE(fairwind::apps::IApp, IID_FAIRWIND_APPS)



#endif //FAIRWIND_IAPP_HPP
