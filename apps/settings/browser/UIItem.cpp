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

        // qDebug() << "fairwind::apps::settings::browser::UIItem path: " << path;

        if (m_ref.isObject()) {
            m_jsonObjectRoot = m_ref.toObject();

            if (m_jsonObjectRoot.contains("name") && m_jsonObjectRoot["name"].isString()) {
                ui->label_Name->setText(m_jsonObjectRoot["name"].toString());
            }

            ui->widget_Container->setVisible(false);
            for (const auto &key: m_jsonObjectRoot.keys()) {
                QJsonValueRef ref = m_jsonObjectRoot[key];
                auto *uiValue = new UIValue(nullptr, settings, ref, path + ":" + key);
                ui->verticalLayout_Container->addWidget(uiValue);
                m_uiValues.append(uiValue);

                connect(uiValue, &UIValue::changed, this, &UIItem::onChanged);
            }

            // If button Expand is pressed, call UIItem::onExpand()
            connect(ui->toolButton_Expand, &QToolButton::clicked, this, &UIItem::onExpand);

            // If button Remove is pressed, call UIItem::onRemove()
            connect(ui->toolButton_Remove, &QToolButton::clicked, this, &UIItem::onRemove);

            // If button Up is pressed, call UIItem::onMoveUp()
            connect(ui->toolButton_Up, &QToolButton::clicked, this, &UIItem::onMoveUp);

            // If button Down is pressed, call UIItem::onMoveDown()
            connect(ui->toolButton_Down, &QToolButton::clicked, this, &UIItem::onMoveDown);
        } else if (m_ref.isString() || m_ref.isDouble() || m_ref.isBool()) {
            auto *uiValue = new UIValue(nullptr, settings, m_ref, path);
            ui->verticalLayout_Container->addWidget(uiValue);
            m_uiValues.append(uiValue);

            connect(uiValue, &UIValue::changed, this, &UIItem::onChanged);
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
            //ui->toolButton_Expand->setText(">");
            ui->toolButton_Expand->setIcon(QIcon(":/resources/images/icons/angle-square-right.png"));
        } else {
            ui->widget_Container->setVisible(true);
            //ui->toolButton_Expand->setText("<");
            ui->toolButton_Expand->setIcon(QIcon(":/resources/images/icons/angle-square-left.png"));

        }
    }

    void UIItem::onChanged() {
        qDebug() << "UIDisplay::onModified()";
        m_ref = m_jsonObjectRoot;
        emit changed();
    }

    void UIItem::onRemove(){
        qDebug() << "UIItem::onRemove()";
        // Emit a signal with a UIItem (chain of responsibility)
        emit removed(this);
    }

    void UIItem::onMoveUp(){
        qDebug() << "UIItem::onMoveUp() " << this;
        m_ref = m_jsonObjectRoot;
        // Emit a signal with a UIItem (chain of responsibility) and the direction
        emit move(this, -1);
    }

    void UIItem::onMoveDown(){
        qDebug() << "UIItem::onMoveDown()";

        // Emit a signal with a UIItem (chain of responsibility) and the direction
        emit move(this, 1);
    }

}

