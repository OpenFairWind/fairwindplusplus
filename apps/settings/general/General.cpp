//
// Created by Raffaele Montella on 19/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_General.h" resolved

#include <QDebug>
#include <FairWindSdk/FairWind.hpp>

#include "General.hpp"
#include "ui_General.h"

namespace fairwind::apps::settings::general {
    General::General(QWidget *parent) :
            QWidget(parent), ui(new Ui::General) {
        ui->setupUi(this);

        // Create the Browser widget
        mBrowser = new browser::Browser();

        // Add the browser to the main layout
        ui->verticalLayout->addWidget(mBrowser);

        connect(mBrowser, &browser::Browser::changed, this, &General::onChanged);
    }

    General::~General() {
        delete ui;
    }

    void General::showEvent(QShowEvent *event) {
        qDebug() << "fairwind::apps::settings::generic::Generic::showEvent";

        // Get the singleton instance of FairWind
        FairWind *fairWind = FairWind::getInstance();
        auto settingsFairWindAppId = fairWind->getSettingsFairWindAppId();
        auto settingsFairWingApp = fairWind->getAppByExtensionId(settingsFairWindAppId);
        auto settings = settingsFairWingApp->getSettings();

        // Get the config object
        auto config = fairWind->getConfig();

        // Set set the browser content
        mBrowser->setJsonObjectRoot(settings, config);

        // Continue with the regular showEvent
        QWidget::showEvent(event);
    }

    QString General::getClassName() const {
        return this->metaObject()->className();
    }

    QImage General::getIcon() const {
        return QImage(":resources/images/icons/generic_icon.png");
    }

    QString General::getName() const {
        return tr("General");
    }

    ui::settings::ISettingsTab *General::getNewInstance() {
        return static_cast<ISettingsTab *>(new General());
    }

    void General::setJsonObjectRoot(ExtendedJsonSchema *settings, QJsonObject jsonObjectRoot) {
        if (mBrowser) {
            mBrowser->setJsonObjectRoot(settings, jsonObjectRoot);
        }
    }

    QJsonObject General::getJsonObjectRoot() {
        if (mBrowser) {
            return mBrowser->getJsonObjectRoot();
        } else {
            return QJsonObject();
        }
    }

    void General::onChanged() {
        // Get the singleton instance of FairWind
        FairWind *fairWind = FairWind::getInstance();
        auto fairWindAppSettingsId = fairWind->getSettingsFairWindAppId();
        if (!fairWindAppSettingsId.isEmpty()){
            auto fairWindAppSettings = fairWind->getAppByExtensionId(fairWindAppSettingsId);
            if (fairWindAppSettings){
                auto config = mBrowser->getJsonObjectRoot();
                fairWindAppSettings->setConfig(config);
            }
        }
    }
} // fairwind::apps::settings::general
