//
// Created by Raffaele Montella on 22/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UIValue.h" resolved

#include <QLineEdit>
#include <QRegExpValidator>
#include <QCheckBox>
#include <utility>
#include <FairWindSdk/util/ExtendedJsonSchema.hpp>
#include "UIValue.hpp"
#include "ui_UIValue.h"
#include "UIArray.hpp"

namespace fairwind::apps::settings::browser {
    UIValue::UIValue(QWidget *parent, ExtendedJsonSchema *settings, QJsonValueRef ref, QString path) :
        QWidget(parent), ui(new Ui::UIValue), m_ref(ref) {
        ui->setupUi(this);

        auto parts = path.split(":");
        m_key = parts[parts.length()-1];
        auto setting = settings->getJsonValueByPath(path);
        qDebug() << "fairwind::apps::settings::browser::UIValue m_key: " << m_key;
        qDebug() << "fairwind::apps::settings::browser:UIValue path: " << path;

        //qDebug() << "UIValue::UIValue: " << m_key;
        if (m_ref.isString() || m_ref.isBool() || m_ref.isDouble()) {
            ui->labelKey->setText(m_key);

            if (m_ref.isString()) {
                auto *widget = new QLineEdit();
                widget->setText(m_ref.toString());
                ui->verticalLayout_Value->addWidget(widget);

                connect(widget, &QLineEdit::textChanged, this, &UIValue::onTextChanged);

                m_widget = widget;
            } else if (m_ref.isDouble()) {
                auto *widget = new QLineEdit();
                widget->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), widget));
                double value = m_ref.toDouble();
                widget->setText(QString::number(value));
                ui->verticalLayout_Value->addWidget(widget);

                connect(widget, &QLineEdit::textChanged, this, &UIValue::onNumberChanged);

                m_widget = widget;
            } else if (m_ref.isBool()) {
                auto *widget = new QCheckBox();
                widget->setText("");
                widget->setChecked(m_ref.toBool());
                ui->verticalLayout_Value->addWidget(widget);

                connect(widget, &QCheckBox::stateChanged, this, &UIValue::onBoolChanged);

                m_widget = widget;
            }
        } else if (m_ref.isArray() || m_ref.isObject()) {

            if (m_ref.isArray()) {
                auto *uiArray = new UIArray(nullptr, settings, m_ref, path);
                ui->verticalLayout_Value->addWidget(uiArray);
                connect(uiArray, &UIArray::changed, this, &UIValue::onArrayChanged);
                m_widget = uiArray;

            } else if (m_ref.isObject()) {
                auto *uiObject = new UIObject(nullptr, settings, m_ref, path);
                ui->verticalLayout_Value->addWidget(uiObject);
                connect(uiObject, &UIObject::changed, this, &UIValue::onObjectChanged);
                m_widget = uiObject;
            }
        }
    }

    UIValue::~UIValue() {
        delete ui;
    }

    void UIValue::onTextChanged() {
        qDebug() << "UIValue::onTextChanged()";
        auto *widget = (QLineEdit *) m_widget;
        QString text = widget->text();
        m_ref = text;
        qDebug() << "m_ref:" << m_ref;
        qDebug() << "m_key:" << m_key;
        emit changed(m_key, this);

    }

    void UIValue::onNumberChanged() {
        qDebug() << "UIValue::onNumberChanged()";
        auto *widget = (QLineEdit *) m_widget;
        double number = widget->text().toDouble();
        m_ref = number;
        qDebug() << "m_ref:" << m_ref;
        emit changed(m_key, this);

    }

    void UIValue::onBoolChanged(int state) {
        qDebug() << "UIValue::onBoolChanged(" << state << ")";
        auto *widget = (QCheckBox *) m_widget;
        m_ref = widget->isChecked();
        qDebug() << "m_ref:" << m_ref;
        emit changed(m_key, this);
    }

    void UIValue::onArrayChanged() {
        qDebug() << "UIValue::onArrayChanged()";
        emit changed(m_key, this);
    }

    void UIValue::onObjectChanged(QString key, UIObject *uiObject) {
        qDebug() << "UIValue::onObjectChanged()";
        m_ref = uiObject->getObject();
        emit changed(m_key, this);
    }

    QJsonValueRef UIValue::getValue() {
        return m_ref;
    }
} // fairwind::apps::settings::browser
