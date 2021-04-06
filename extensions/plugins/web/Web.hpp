//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_WEB_HPP
#define FAIRWIND_WEB_HPP


#include "../../../include/IFairWindPlugin.hpp"
#include "../../../include/FairWindPlugin.hpp"

namespace fairwind::extensions::plugins::web {
    class Web : public QObject, public FairWindPlugin, public IFairWindPlugin {
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

    private:
        void toolButton_home_clicked();

        QWidget *m_widgetWebApp= nullptr;
        QString m_url;
    };
}



#endif //FAIRWIND_WEB_HPP
