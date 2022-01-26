//
// Created by Raffaele Montella on 10/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UIDisplay.h" resolved

#include <QJsonObject>
#include "UIItem.hpp"
#include "ui_UIItem.h"
#include "UIObject.hpp"

namespace fairwind::apps::settings::browser {
    UIItem::UIItem(QWidget *parent, ExtendedJsonSchema *settings, QJsonValueRef mRef, QString path) :
            QWidget(parent), ui(new Ui::UIItem), m_ref(mRef) {
        ui->setupUi(this);

        qDebug() << "fairwind::apps::settings::browser::UIItem path: " << path;

        if (m_ref.isObject()) {
            m_jsonObjectRoot = m_ref.toObject();

            ui->label_Class->setText(m_jsonObjectRoot["class"].toString());
            ui->widget_Container->setVisible(false);
            for (const auto &key: m_jsonObjectRoot.keys()) {
                QJsonValueRef ref = m_jsonObjectRoot[key];
                auto *uiValue = new UIValue(nullptr, settings, ref, path + ":" + key);
                ui->verticalLayout_Container->addWidget(uiValue);
                m_uiValues.append(uiValue);

                connect(uiValue, &UIValue::changed, this, &UIItem::onChanged);
            }


            connect(ui->toolButton_Expand, &QToolButton::clicked, this, &UIItem::onExpand);
        }
    }

    UIItem::~UIItem() {
        for (const auto item: m_uiValues) {
            delete item;
        }
        delete ui;
    }

    void UIItem::onExpand() {
        qDebug() << "UIItem::onExpand()";
        if (ui->widget_Container->isVisible()) {
            ui->widget_Container->setVisible(false);
            ui->toolButton_Expand->setText(">");
        } else {
            ui->widget_Container->setVisible(true);
            ui->toolButton_Expand->setText("<");
        }
    }

    void UIItem::onChanged() {
        qDebug() << "UIDisplay::onModified()";
        m_ref = m_jsonObjectRoot;
        emit changed();
    }

}

