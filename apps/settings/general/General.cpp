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
    }

    General::~General() {
        delete ui;
    }

    void General::showEvent(QShowEvent *event) {
        qDebug() << "fairwind::apps::settings::generic::Generic::showEvent";

        // Get the singleton instance of FairWind
        FairWind *fairWind = FairWind::getInstance();

        // Get the config object
        m_config = fairWind->getConfig();

        // Set set the browser content
        mBrowser->setJsonObjectRoot(m_config);

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

    void General::setJsonObjectRoot(QJsonObject jsonObjectRoot) {
        if (mBrowser) {
            mBrowser->setJsonObjectRoot(jsonObjectRoot);
        }
    }

    QJsonObject General::getJsonObjectRoot() {
        if (mBrowser) {
            return mBrowser->getJsonObjectRoot();
        } else {
            return QJsonObject();
        }
    }
} // fairwind::apps::settings::general
