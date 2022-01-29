//
// Created by Raffaele Montella on 19/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Browser.h" resolved

#include "Browser.hpp"

#include <utility>
#include <QJsonDocument>
#include <QFile>
#include "ui_Browser.h"
#include "UIValue.hpp"

namespace fairwind::apps::settings::browser {
    Browser::Browser(QWidget *parent) :
            QWidget(parent), ui(new Ui::Browser) {
        ui->setupUi(this);

    }

    Browser::~Browser() {
        for (const auto item:m_uiValues) {
            delete item;
        }

        m_uiValues.clear();

        if (m_settings){
            delete m_settings;
        }

        delete ui;
    }

    void Browser::setJsonObjectRoot(ExtendedJsonSchema *settings, QJsonObject jsonObjectRoot) {

        for (const auto item:m_uiValues) {
            delete item;
        }

        m_uiValues.clear();

        m_settings = settings;
        m_jsonObjectRoot = std::move(jsonObjectRoot);

        int counter = 0;
        for (QJsonValueRef item: m_jsonObjectRoot) {
            QString key = m_jsonObjectRoot.keys()[counter];
            qDebug() << "Browser::setJsonObjectRoot key:" << key;

            auto *uiValue = new UIValue(nullptr, m_settings, item,key);
            ui->verticalLayout->addWidget(uiValue);
            m_uiValues.append(uiValue);


            connect(uiValue, &UIValue::changed, this, &Browser::onChanged);
            counter++;
        }


    }

    QJsonObject Browser::getJsonObjectRoot() {
        return m_jsonObjectRoot;
    }

    void Browser::onChanged(QString key, UIValue *uiValue) {
        qDebug() << "Browser::onChanged()::key: " << key;
        m_jsonObjectRoot[key] = uiValue->getValue();
        emit changed();
    }


} // fairwind::apps::settings::browser
