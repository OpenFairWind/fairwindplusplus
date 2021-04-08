//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_WEB_HPP
#define FAIRWIND_WEB_HPP


#include <include/FairWindExtension.hpp>
#include "../../../include/IFairWindPlugin.hpp"


namespace fairwind::extensions::plugins::web {
    class Web : public QObject, FairWindExtension, IFairWindPlugin {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_PLUGINS FILE "manifest.json")
        Q_INTERFACES(fairwind::extensions::plugins::IFairWindPlugin)

    public:
        ~Web() = default;

        void init(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;

    private:
        QJsonObject m_metaData;

        void toolButton_home_clicked();

        QWidget *m_widgetWebApp= nullptr;
        QString m_url;
    };
}



#endif //FAIRWIND_WEB_HPP
