//
// Created by Raffaele Montella on 19/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Browser.h" resolved

#include "Browser.hpp"

#include <utility>
#include "ui_Browser.h"

namespace fairwind::apps::settings::browser {
    Browser::Browser(QWidget *parent) :
            QWidget(parent), ui(new Ui::Browser) {
        ui->setupUi(this);

    }

    Browser::~Browser() {
        for (const auto item:m_items) {
            delete item;
        }

        m_items.clear();

        delete ui;
    }

    void Browser::setJsonObjectRoot(QJsonObject jsonObjectRoot) {

        for (const auto item:m_items) {
            delete item;
        }

        m_items.clear();

        m_jsonObjectRoot = std::move(jsonObjectRoot);

        for (const auto& key:m_jsonObjectRoot.keys()) {
            qDebug() << "key:" << key;
            QJsonValueRef ref = m_jsonObjectRoot[key];
            auto *uiJsonObject = new UIObject(nullptr, ref,key);
            ui->verticalLayout->addWidget(uiJsonObject);
            m_items.append(uiJsonObject);
        }
    }

    QJsonObject Browser::getJsonObjectRoot() {
        return m_jsonObjectRoot;
    }


} // fairwind::apps::settings::browser
