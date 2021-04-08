//
// Created by Raffaele Montella on 03/04/21.
//

#ifndef FAIRWIND_IFAIRWINDPLUGIN_HPP
#define FAIRWIND_IFAIRWINDPLUGIN_HPP


#include <QtPlugin>
#include <QString>
#include <QImage>
#include <QMainWindow>

#define IID_FAIRWIND_PLUGINS "it.uniparthenope.fairwind.plugins"

namespace fairwind::extensions::plugins {

    class IFairWindPlugin {
    public:
        virtual ~IFairWindPlugin() = default;

        virtual void init(QJsonObject *metaData) = 0;

        virtual QString getId() const = 0;
        virtual QString getName() const = 0;
        virtual QString getDesc() const = 0;

        virtual QImage getIcon() const = 0;
        virtual QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) = 0;

    };

}

Q_DECLARE_INTERFACE(fairwind::extensions::plugins::IFairWindPlugin, IID_FAIRWIND_PLUGINS)


#endif //FAIRWIND_IFAIRWINDPLUGIN_HPP
