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
#include "ui_GC1530_Settings.h"
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
        QWidget *onSettings(QTabWidget *tabWidgets) override;

        QJsonObject getConfig() override;
        QJsonObject getMetaData() override;

    private:
        void toolButton_home_clicked();

        Ui::GC1530 *ui;
        Ui::gc1530_Settings *uiSettings;
        QWidget *m_widget= nullptr;
        WebView *m_webView = nullptr;

        QWebEngineProfile *m_profile;

        QString m_url;
    };
}

#endif //GC1530_HPP
