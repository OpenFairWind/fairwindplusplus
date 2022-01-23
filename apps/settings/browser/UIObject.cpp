//
// Created by Raffaele Montella on 09/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UIJsonObject.h" resolved

#include <QDebug>
#include <QLineEdit>
#include <utility>
#include <QJsonArray>
#include <QCheckBox>
#include <QRegExpValidator>
#include <QGroupBox>
#include "UIObject.hpp"
#include "UIArray.hpp"
#include "ui_UIObject.h"
#include "UIValue.hpp"


namespace fairwind::apps::settings::browser {
    UIObject::UIObject(QWidget *parent, QJsonValueRef ref, QString key) :
            QWidget(parent), ui(new Ui::UIObject), m_ref(ref), m_key(std::move(key)) {
        ui->setupUi(this);

        ui->groupBox->setTitle(m_key);

        m_jsonObject = m_ref.toObject();
        int counter = 0;
        for (QJsonValueRef item: m_jsonObject) {
            QString key = m_jsonObject.keys()[counter];
            qDebug() << "UIObject::UIObject key: " << key;
            auto *uiValue= new UIValue(nullptr, item,key);
            ui->verticalLayout_Container->addWidget(uiValue);
            m_uiValues.append(uiValue);

            connect(uiValue, &UIValue::changed, this, &UIObject::onChanged);
            counter++;
        }
        //connect(ui->pushButton_Add, &QPushButton::clicked, this, &UIObject::onAdd);

    }

    UIObject::~UIObject() {
        for (auto item: m_uiValues) {
            delete item;
        }
        delete ui;
    }


    void UIObject::onAdd() {

    }

    void UIObject::onChanged() {
        qDebug() << "UIObject::onChanged";
        emit changed();
    }


}
