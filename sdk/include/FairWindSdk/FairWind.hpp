//
// Created by Raffaele Montella on 03/04/21.
//

#ifndef FAIRWIND_FAIRWIND_HPP
#define FAIRWIND_FAIRWIND_HPP

#include <QString>
#include <map>
#include <QJsonDocument>
#include <QDir>

#include <QGeoView/QGVLayer.h>

#include "FairWindSDK.hpp"
#include "IFairWindApp.hpp"
#include "ILayer.hpp"
#include "SignalKDocument.hpp"
#include "AppItem.hpp"
#include "IDisplay.hpp"
#include "IConnection.hpp"
#include "ILayout.hpp"
#include "ISettings.hpp"
#include "ISettingsTab.hpp"

namespace fairwind {
    /*
     * FairWind
     * Singleton used to handle the entire FairWind ecosystem in a centralized way
     */
    class FAIRWINDSDK_LIB_DECL FairWind: public QObject {
        Q_OBJECT
    public:
        static FairWind *getInstance();

        void loadApps();



        void setApplicationDirPath(QString qString);
        void loadConfig();

        SignalKDocument *getSignalKDocument();

        apps::IFairWindApp *getAppByExtensionId(const QString& id);
        QList<QString> getExtensionsIds();
        QList<QString> getExtensionsHashes();
        AppItem *getAppItemByHash(QString hash);
        QString getAppHashById(QString appId);

        bool registerLayer(fairwind::layers::ILayer *dummy);
        layers::ILayer *instanceLayer(const QString& className);

        bool registerDisplay(fairwind::displays::IDisplay *dummy);
        displays::IDisplay *instanceDisplay(const QString& className);

        bool registerConnection(fairwind::connections::IConnection *dummy);
        connections::IConnection *instanceConnection(const QString& className);

        bool registerLayout(fairwind::layouts::ILayout *dummy);
        layouts::ILayout *instanceLayout(const QString& className);

        bool registerSettingsTab(fairwind::ui::settings::ISettingsTab *dummy);
        bool registerSettings(fairwind::ui::settings::ISettings *dummy);
        ui::settings::ISettingsTab *instanceSettingsTab(const QString& className);
        ui::settings::ISettings *instanceSettings(const QString& className);

        QMap<QString, fairwind::layers::ILayer *> *getLayers();
        QMap<QString, fairwind::displays::IDisplay *> *getDisplays();
        QMap<QString, fairwind::connections::IConnection *> *getConnections();
        QMap<QString, fairwind::layouts::ILayout *> *getLayouts();
        QMap<QString, fairwind::ui::settings::ISettingsTab *> *getSettings();

        QList<fairwind::connections::IConnection *> *getConnectionsList();
        QList<ui::settings::ISettingsTab *> *getSettingsList();

        QJsonObject getConfig();

        QString getMyDataFairWindAppId();
        QString getMOBFairWindAppId();
        QString getLauncherFairWindAppId();
        QString getAlarmsFairWindAppId();
        QString getSettingsFairWindAppId();


        void setMainWindow(QMainWindow *mainWindow);
        QMainWindow *getMainWindow();

    private:
        QMainWindow *m_mainWindow;

        QString mMyDataFairWindAppId;
        QString mMOBFairWindAppId;
        QString mLauncherFairWindAppId;
        QString mAlarmsFairWindAppId;
        QString mSettingsFairWindAppId;

        SignalKDocument m_signalkDocument;

        QMap<QString, fairwind::apps::IFairWindApp *> m_mapAppId2FairWindApp;
        QMap<QString, AppItem *> m_mapHash2AppItem;
        QMap<QString, QString> m_mapAppId2Hash;

        QList<fairwind::connections::IConnection *> m_listConnections;

        QString m_applicationDirPath;
        FairWind();
        inline static FairWind *m_instance = nullptr;

        QMap<QString, layers::ILayer *> m_registeredLayers;
        QMap<QString, displays::IDisplay *> m_registeredDisplays;
        QMap<QString, connections::IConnection *> m_registeredConnections;
        QMap<QString, layouts::ILayout *> m_registeredLayouts;
        QMap<QString, ui::settings::ISettings *> m_registeredSettings;
        QMap<QString, ui::settings::ISettingsTab *> m_registeredSettingsTab;
        QList<ui::settings::ISettingsTab *> m_listSettings;

        QDir m_appsRoot;
        QDir m_dataRoot;


    };
}

#endif //FAIRWIND_FAIRWIND_HPP