//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef GC1530_HPP
#define GC1530_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/AppBase.hpp>
#include <FairWindSdk/IApp.hpp>
#include <QWebEngineProfile>
#include "ui_GC1530.h"
#include "WebView.hpp"

namespace it::gov::guardiacostiera::gc1530 {
    class GC1530 : public QObject, ::fairwind::AppBase, ::fairwind::apps::IApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IApp)

    public:
        ~GC1530() = default;

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
        QJsonObject getSettings() override;
        void setSettings(QJsonObject config) override;
        QJsonObject getMetaData() override;

    private:
        void toolButton_home_clicked();

        Ui::GC1530 *ui;
        QWidget *m_widget= nullptr;
        WebView *m_webView = nullptr;

        QWebEngineProfile *m_profile;

        QString m_url;
    };
}

#endif //GC1530_HPP
