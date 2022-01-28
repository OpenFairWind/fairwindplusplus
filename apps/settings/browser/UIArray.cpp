//
// Created by Raffaele Montella on 10/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UIArrayDisplays.h" resolved

#include <QJsonArray>
#include <QLabel>
#include <FairWindSdk/util/ExtendedJsonSchema.hpp>
#include "UIArray.hpp"
#include "ui_UIArray.h"
#include "UIItem.hpp"

namespace fairwind::apps::settings::browser {
    UIArray::UIArray(QWidget *parent, ExtendedJsonSchema *settings, QJsonValueRef mRef, QString path) :
            QWidget(parent), ui(new Ui::UIArray), m_ref(mRef) {
        ui->setupUi(this);

        auto parts = path.split(".");
        m_key = parts[parts.length()-1];
        m_settings = settings;
        auto setting = settings->getJsonValueByPath(path);
        // qDebug() << "fairwind::apps::settings::browser::UIArray m_key: " << m_key;
        // qDebug() << "fairwind::apps::settings::browser::UIArray path: " << path;

        ui->groupBox->setTitle(m_key);

        m_jsonArray = m_ref.toArray();
        int idx=0;
        for (QJsonValueRef item: m_jsonArray) {
            auto *uiItem = new UIItem(nullptr, settings, item, path + ":" + QString::number(idx));
            ui->verticalLayout_Container->addWidget(uiItem);
            m_uiItems.append(uiItem);

            connect(uiItem, &UIItem::changed, this, &UIArray::onChanged);
            idx++;
        }
        connect(ui->pushButton_Add, &QPushButton::clicked, this, &UIArray::onAdd);
    }

    UIArray::~UIArray() {
        for (auto item: m_uiItems) {
            delete item;
        }
        delete ui;
    }

    void UIArray::onChanged() {
        qDebug() << "UIArray::onChanged()";
        m_ref = m_jsonArray;
        emit changed(m_key, this);
    }

    void UIArray::onAdd() {
        qDebug() << "UIArray::onAdd()";
        QJsonObject jsonObject;
        jsonObject["class"] = "it::uniparthenope::fairwind::MyClass";
        jsonObject["active"] = false;
        m_jsonArray.append(jsonObject);

        QJsonValueRef ref = m_jsonArray[m_jsonArray.size() - 1];
        auto *uiItem = new UIItem(nullptr, m_settings, ref, m_path + ":" + QString::number(m_jsonArray.size() - 1));
        ui->verticalLayout_Container->addWidget(uiItem);
        m_uiItems.append(uiItem);

        connect(uiItem, &UIItem::changed, this, &UIArray::onChanged);


        m_ref = m_jsonArray;
        emit changed(m_key, this);
    }

    QJsonValueRef UIArray::getArray() {
        return m_ref;
    }
}


