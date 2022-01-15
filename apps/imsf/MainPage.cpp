//
// Created by Raffaele Montella on 10/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "MainPage.hpp"
#include "ui_MainPage.h"
#include "Flag.hpp"

namespace fairwind::apps::imsf {
    MainPage::MainPage(QWidget *parent, fairwind::apps::IFairWindApp *fairWindApp) :
            PageBase(parent, fairWindApp), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);

        qDebug() << "MainPage::MainPage(QWidget *parent)";
        QFile contentFile(":resources/content/data.json");
        if (contentFile.exists()) {
            contentFile.open(QFile::ReadOnly);
            if (contentFile.isOpen()) {
                QJsonDocument jsonDocument = QJsonDocument::fromJson(contentFile.readAll());
                m_jsonObject = jsonDocument.object();
                if (m_jsonObject.contains("flags") && m_jsonObject["flags"].isObject()) {
                    QJsonObject jsonObjectFlags = m_jsonObject["flags"].toObject();
                    for (auto key:jsonObjectFlags.keys()) {
                        if (jsonObjectFlags[key].isObject()) {
                            auto *flag = new Flag(nullptr, jsonObjectFlags[key].toObject());
                            ui->verticalLayout_Flags->addWidget(flag);
                        }
                    }
                }
            }
        }
    }

    MainPage::~MainPage() {
        delete ui;
    }


} // fairwind::apps::imsf
