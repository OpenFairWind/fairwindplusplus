//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_NATIVE_HPP
#define FAIRWIND_NATIVE_HPP


#include "../../../include/IFairWindPlugin.hpp"
#include "../../../include/FairWindPlugin.hpp"


namespace fairwind::extensions::plugins::native {
    class Native : public QObject, public FairWindPlugin, public IFairWindPlugin {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_PLUGINS FILE "manifest.json")
        Q_INTERFACES(fairwind::extensions::plugins::IFairWindPlugin)

    public:
        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;
        void setMetaData(QJsonObject &metaData) override;
        QImage getIcon() const override;

        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;
    };
}


#endif //FAIRWIND_NATIVE_HPP
