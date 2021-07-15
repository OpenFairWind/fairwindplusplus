//
// Created by Raffaele Montella on 15/07/21.
//

#ifndef FAIRWIND_ENTERTAINMENT_HPP
#define FAIRWIND_ENTERTAINMENT_HPP

#include <QObject>
#include <QtPlugin>
#include <FairWindSdk/AppBase.hpp>
#include <FairWindSdk/IApp.hpp>
#include "ui_Entertainment.h"
#include "ui_Entertainment_Settings.h"

namespace fairwind::apps::entertainment {
    class Entertainment : public QObject, AppBase, IApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::apps::IApp)

    public:
        ~Entertainment() = default;

        void onInit(QJsonObject *metaData) override;

        QString getId() const override;
        QString getName() const override;
        QString getDesc() const override ;

        QImage getIcon() const override;
        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) override;
        QWidget *onSettings(QTabWidget *tabWidgets) override;

        QJsonObject getConfig() override;
        QJsonObject getMetaData() override;

    private:
        Ui::Entertainment *ui;
        Ui::entertainment_Settings *uiSettings;
        QWidget *m_widget= nullptr;
    };
}

#endif //FAIRWIND_ENTERTAINMENT_HPP
