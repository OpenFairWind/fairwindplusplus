//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_NATIVE_HPP
#define FAIRWIND_NATIVE_HPP

#include <FairWindAppBase.hpp>
#include <IFairWindApp.hpp>

namespace fairwind::apps::native {
    class Native : public QObject, FairWindAppBase, IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

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
