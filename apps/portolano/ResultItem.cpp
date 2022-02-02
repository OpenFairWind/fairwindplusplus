//
// Created by Raffaele Montella on 31/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ResultItem.h" resolved

#include <QJsonArray>
#include <QDir>
#include "ResultItem.hpp"
#include "ui_ResultItem.h"

namespace fairwind::apps::portolano {
    ResultItem::ResultItem(QWidget *parent, QJsonObject feature) :
            QWidget(parent), ui(new Ui::ResultItem), mFeature(feature) {
        ui->setupUi(this);

        if (mFeature.contains("properties") && mFeature["properties"].isObject()) {
            auto jsonObjectProperties = mFeature["properties"].toObject();

            if (jsonObjectProperties.contains("mapId") && jsonObjectProperties["mapId"].isString()) {
                auto mapId = jsonObjectProperties["mapId"].toString();
                QStringList list = mapId.split("_");
                QString iconPath = ":/resources/images/ports/"+list[0]+QDir::separator()+mapId+".jpg";
                // qDebug() << "iconPath: " << iconPath;
                ui->label_Icon->setPixmap(QPixmap::fromImage(QImage(iconPath)));
            }

            if (jsonObjectProperties.contains("name") && jsonObjectProperties["name"].isString()) {
                auto name = jsonObjectProperties["name"].toString();
                ui->label_Name->setText(name);
            }
            if (jsonObjectProperties.contains("description") && jsonObjectProperties["description"].isString()) {
                auto description = jsonObjectProperties["description"].toString();
                ui->textEdit_Description->setText(description);
            }

            if (jsonObjectProperties.contains("contacts")) {

                if (jsonObjectProperties["contacts"].isString()) {
                    auto contact = jsonObjectProperties["contacts"].toString();
                    ui->listWidget_Contacts->addItem(contact);

                } else if (jsonObjectProperties["contacts"].isArray()) {
                    auto contacts = jsonObjectProperties["contacts"].toArray();
                    for (auto contact: contacts) {
                        if (contact.isString()) {
                            ui->listWidget_Contacts->addItem(contact.toString());
                        }
                    }
                }
            }
        }
    }

    ResultItem::~ResultItem() {
        delete ui;
    }


} // fairwind::apps::portolano
