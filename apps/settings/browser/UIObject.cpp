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
#include <FairWindSdk/util/ExtendedJsonSchema.hpp>
#include "UIObject.hpp"
#include "UIArray.hpp"
#include "ui_UIObject.h"
#include "UIValue.hpp"


namespace fairwind::apps::settings::browser {
    UIObject::UIObject(QWidget *parent, ExtendedJsonSchema *settings, QJsonValueRef ref, QString path) :
            QWidget(parent), ui(new Ui::UIObject), m_ref(ref) {
        ui->setupUi(this);

        auto parts = path.split(".");
        m_key = parts[parts.length()-1];
        auto setting = settings->getJsonValueByPath(path);
        qDebug() << "fairwind::apps::settings::browser::UIObject m_key: " << m_key;
        qDebug() << "fairwind::apps::settings::browser::UIObject path: " << path;

        ui->groupBox->setTitle(m_key);

        m_jsonObject = m_ref.toObject();
        int counter = 0;
        for (QJsonValueRef item: m_jsonObject) {
            QString key = m_jsonObject.keys()[counter];
            //qDebug() << "UIObject::UIObject key: " << key;
            auto *uiValue= new UIValue(nullptr, settings, item, path + ":" + key);
            ui->verticalLayout_Container->addWidget(uiValue);
            m_mapUiValues[key] = uiValue;

            connect(uiValue, &UIValue::changed, this, &UIObject::onChanged);
            counter++;
        }
        //connect(ui->pushButton_Add, &QPushButton::clicked, this, &UIObject::onAdd);

    }

    UIObject::~UIObject() {
        for (auto item: m_mapUiValues) {
            delete item;
        }
        delete ui;
    }


    void UIObject::onAdd() {

    }

    void UIObject::onChanged(QString key, UIValue *uiValue) {
        qDebug() << "UIObject::onChanged";
        m_jsonObject[key] = uiValue->getValue();
        m_ref = m_jsonObject;
        emit changed(m_key, this);
    }

    QJsonValueRef UIObject::getObject() {
        return m_ref;
    }


}
