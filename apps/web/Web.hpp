//
// Created by Raffaele Montella on 01/04/21.
//

#ifndef FAIRWIND_WEB_HPP
#define FAIRWIND_WEB_HPP


#include <IFairWindApp.hpp>
#include <FairWindAppBase.hpp>
#include <QWebEngineProfile>

namespace fairwind::apps::web {
    class Web : public QObject, FairWindAppBase, IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IFairWindApp)

    public:
        ~Web() = default;

        void onInit(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;
        QWidget *onSettings(QTabWidget *tabWidgets) override;

    private:
        QWebEngineProfile *m_profile;

        void toolButton_home_clicked();

        QWidget *m_widgetWebApp= nullptr;
        QString m_url;
    };
}



#endif //FAIRWIND_WEB_HPP
