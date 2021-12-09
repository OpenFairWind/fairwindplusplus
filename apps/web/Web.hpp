//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_WEB_HPP
#define FAIRWIND_WEB_HPP


#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/AppBase.hpp>
#include <QWebEngineProfile>

namespace fairwind::apps::web {
    class Web : public QObject, AppBase, IApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IApp)

    public:
        ~Web() = default;

        void onInit(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;
        QString getVersion() const override;
        QString getVendor() const override;
        QString getCopyright() const override;
        QString getLicense() const override;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) override;
        void updateSettings(QString settingsID, QString newValue) override;

        QJsonObject getConfig() override;
        void setConfig(QJsonObject config) override;
        QJsonObject getMetaData() override;

    private:
        QWebEngineProfile *m_profile;

        void toolButton_home_clicked();

        QWidget *m_widgetWebApp= nullptr;
        QString m_url;
    };
}



#endif //FAIRWIND_WEB_HPP
