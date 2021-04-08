//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_NATIVE_HPP
#define FAIRWIND_NATIVE_HPP


#include "../../../include/IFairWindPlugin.hpp"
#include "../../../include/FairWindExtension.hpp"


namespace fairwind::extensions::plugins::native {
    class Native : public QObject, FairWindExtension, IFairWindPlugin {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_PLUGINS FILE "manifest.json")
        Q_INTERFACES(fairwind::extensions::plugins::IFairWindPlugin)

    public:
        ~Native() = default;

        void init(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;

    private:

    };
}


#endif //FAIRWIND_NATIVE_HPP
