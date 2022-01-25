//
// Created by Raffaele Montella on 10/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UIArrayDisplays.h" resolved

#include <QJsonArray>
#include <QLabel>
#include "UIArray.hpp"
#include "ui_UIArray.h"
#include "UIItem.hpp"

namespace fairwind::apps::settings::browser {
    UIArray::UIArray(QWidget *parent, QJsonValueRef mRef, QString key) :
            QWidget(parent), ui(new Ui::UIArray), m_ref(mRef), m_key(std::move(key)) {
        ui->setupUi(this);

        ui->groupBox->setTitle(m_key);

        m_jsonArray = m_ref.toArray();
        for (QJsonValueRef item: m_jsonArray) {
            if (item.isObject()) {
                auto *uiItem = new UIItem(nullptr, item);
                ui->verticalLayout_Container->addWidget(uiItem);
                m_uiItems.append(uiItem);

                connect(uiItem, &UIItem::changed, this, &UIArray::onChanged);
            }
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
        auto *uiItem = new UIItem(nullptr, ref);
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


