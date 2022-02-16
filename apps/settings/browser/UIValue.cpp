//
// Created by Raffaele Montella on 22/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UIValue.h" resolved

#include <QLineEdit>
#include <QRegExpValidator>
#include <QCheckBox>
#include <utility>
#include <FairWindSdk/util/ExtendedJsonSchema.hpp>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include "UIValue.hpp"
#include "ui_UIValue.h"
#include "UIArray.hpp"

#include <math.h>

namespace fairwind::apps::settings::browser {
    UIValue::UIValue(QWidget *parent, ExtendedJsonSchema *settings, QJsonValueRef ref, QString path) :
        QWidget(parent), ui(new Ui::UIValue), m_ref(ref) {
        ui->setupUi(this);

        auto parts = path.split(":");
        m_key = parts[parts.length()-1];
        auto setting = settings->getJsonValueByPath(path).toObject();
        //qDebug() << "fairwind::apps::settings::browser::UIValue m_key: " << m_key;
        // qDebug() << "fairwind::apps::settings::browser:UIValue path: " << path;
        // qDebug() << "fairwind::apps::settings::browser::UIValue setting: " << setting;

        QJsonObject jsonObjectFairwind;

        if (setting.contains("fairwind") && setting["fairwind"].isObject()) {
            jsonObjectFairwind = setting["fairwind"].toObject();

            if (jsonObjectFairwind.contains("postfix") && jsonObjectFairwind["postfix"].isString()) {
                ui->labelPostfix->setText(jsonObjectFairwind["postfix"].toString());
            }
        }

        QString title;
        if (setting.contains("title") && setting["title"].isString()){
            title = setting["title"].toString();

        }
        else {
            title = m_key;
        }

        QString description = "";
        if (setting.contains("description") && setting["description"].isString()){
            description = setting["description"].toString();

        }

        if (m_ref.isString() || m_ref.isBool() || m_ref.isDouble()) {
            ui->labelKey->setText(title);

            if (m_ref.isString()) {
                QString text = m_ref.toString();
                if (text.isEmpty() && setting.contains("default") && setting["default"].isString()){
                    text = setting["default"].toString();
                }

                if (jsonObjectFairwind.contains("domain") && jsonObjectFairwind["domain"].isArray()) {
                    auto jsonItems =  jsonObjectFairwind["domain"].toArray();
                    auto *widget = new QComboBox();
                    widget->setEditable(false);

                    int index = 0;
                    for (auto item: jsonItems){
                        if (item.isObject()) {
                            auto jsonObjectItem = item.toObject();
                            if (jsonObjectItem.contains("key") && jsonObjectItem["key"].isString() &&
                                jsonObjectItem.contains("value") && jsonObjectItem["value"].isString()) {

                                if (jsonObjectItem.contains("icon") && jsonObjectItem["icon"].isString()) {
                                    QIcon icon = QIcon(QPixmap::fromImage(QImage(jsonObjectItem["icon"].toString())));

                                    widget->addItem(icon,jsonObjectItem["key"].toString(), jsonObjectItem["value"].toString());
                                } else {
                                    widget->addItem(jsonObjectItem["key"].toString(),
                                                    jsonObjectItem["value"].toString());
                                }
                                if (text == jsonObjectItem["value"].toString()) {
                                    widget->setCurrentIndex(index);
                                }
                            }
                        }
                        index++;
                    }

                    ui->verticalLayout_Value->addWidget(widget);
                    connect(widget, &QComboBox::currentTextChanged, this, &UIValue::onComboBoxCurrentTextChanged);

                    m_widget = widget;

                }
                else if (setting.contains("enum") && setting["enum"].isArray()){
                    auto jsonItems = setting["enum"].toArray();
                    auto *widget = new QComboBox();
                    widget->setEditable(false);

                    for (auto item: jsonItems){
                        widget->addItem(item.toString(), item.toString());
                    }
                    ui->verticalLayout_Value->addWidget(widget);
                    widget->setCurrentText(text);
                    widget->setToolTip(description);

                    connect(widget, &QComboBox::currentTextChanged, this, &UIValue::onComboBoxCurrentTextChanged);

                    m_widget = widget;
                }
                else if (jsonObjectFairwind.contains("multiline") && jsonObjectFairwind["multiline"].isBool() && jsonObjectFairwind["multiline"].toBool()) {
                    auto *widget = new QTextEdit();
                    widget->setText(text);
                    ui->verticalLayout_Value->addWidget(widget);
                    widget->setToolTip(description);

                    if (setting.contains("readOnly") && setting["readOnly"].isBool() && setting["readOnly"].toBool()){
                        widget->setReadOnly(true);
                    }

                    connect(widget, &QTextEdit::textChanged, this, &UIValue::onTextChanged);

                    m_widget = widget;
                }
                else {
                    auto *widget = new QLineEdit();
                    if (setting.contains("pattern") && setting["pattern"].isString()){
                        widget->setValidator(new QRegExpValidator(QRegExp(setting["pattern"].toString()), widget));
                    }
                    widget->setText(text);
                    ui->verticalLayout_Value->addWidget(widget);
                    widget->setToolTip(description);

                    if (setting.contains("readOnly") && setting["readOnly"].isBool() && setting["readOnly"].toBool()){
                        widget->setReadOnly(true);
                    }


                    if (jsonObjectFairwind.contains("password") && jsonObjectFairwind["password"].isBool() && jsonObjectFairwind["password"].toBool()) {
                        widget->setEchoMode(QLineEdit::Password);
                    }

                    connect(widget, &QLineEdit::textChanged, this, &UIValue::onTextChanged);

                    m_widget = widget;
                }
            } else if (m_ref.isDouble()) {
                double value = m_ref.toDouble();
                if (isnan(value) && setting.contains("default") && setting["default"].isDouble()){
                    value = setting["default"].toDouble();
                }

                if (jsonObjectFairwind.contains("domain") && jsonObjectFairwind["domain"].isArray()) {
                    auto jsonItems =  jsonObjectFairwind["domain"].toArray();
                    auto *widget = new QComboBox();
                    widget->setEditable(false);

                    int index = 0;
                    for (auto item: jsonItems){
                        if (item.isObject()) {
                            auto jsonObjectItem = item.toObject();
                            if (jsonObjectItem.contains("key") && jsonObjectItem["key"].isString() &&
                                jsonObjectItem.contains("value") && jsonObjectItem["value"].isDouble()) {

                                if (jsonObjectItem.contains("icon") && jsonObjectItem["icon"].isString()) {
                                    QIcon icon = QIcon(QPixmap::fromImage(QImage(jsonObjectItem["icon"].toString())));

                                    widget->addItem(icon,jsonObjectItem["key"].toString(), jsonObjectItem["value"].toDouble());
                                } else {
                                    widget->addItem(jsonObjectItem["key"].toString(),
                                                    jsonObjectItem["value"].toDouble());
                                }
                                if (value == jsonObjectItem["value"].toDouble()) {
                                    widget->setCurrentIndex(index);
                                }
                            }
                        }
                        index++;
                    }

                    ui->verticalLayout_Value->addWidget(widget);
                    connect(widget, &QComboBox::currentTextChanged, this, &UIValue::onComboBoxCurrentTextChanged);

                    m_widget = widget;

                } else {

                    auto *widget = new QDoubleSpinBox();

                    if ((setting.contains("minimum") && setting["minimum"].isDouble()) &&
                        (setting.contains("maximum") && setting["maximum"].isDouble())) {
                        widget->setMinimum(setting["minimum"].toDouble());
                        widget->setMaximum(setting["maximum"].toDouble());
                    }

                    widget->setValue(value);
                    ui->verticalLayout_Value->addWidget(widget);
                    widget->setToolTip(description);
                    connect(widget, &QDoubleSpinBox::textChanged, this, &UIValue::onNumberTextChanged);
                    connect(widget, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                            &UIValue::onNumberSelectChanged);

                    m_widget = widget;
                }
            } else if (m_ref.isBool()) {

                if (jsonObjectFairwind.contains("domain") && jsonObjectFairwind["domain"].isArray()) {
                    auto jsonItems =  jsonObjectFairwind["domain"].toArray();
                    auto *widget = new QComboBox();
                    widget->setEditable(false);

                    int index = 0;
                    for (auto item: jsonItems){
                        if (item.isObject()) {
                            auto jsonObjectItem = item.toObject();
                            if (jsonObjectItem.contains("key") && jsonObjectItem["key"].isString() &&
                                jsonObjectItem.contains("value") && jsonObjectItem["value"].isBool()) {

                                if (jsonObjectItem.contains("icon") && jsonObjectItem["icon"].isString()) {
                                    QIcon icon = QIcon(QPixmap::fromImage(QImage(jsonObjectItem["icon"].toString())));

                                    widget->addItem(icon,jsonObjectItem["key"].toString(), jsonObjectItem["value"].toBool());
                                } else {
                                    widget->addItem(jsonObjectItem["key"].toString(), jsonObjectItem["value"].toBool());
                                }
                                if (m_ref.toBool() == jsonObjectItem["value"].toBool()) {
                                    widget->setCurrentIndex(index);
                                }
                            }
                        }
                        index++;
                    }

                    ui->verticalLayout_Value->addWidget(widget);
                    connect(widget, &QComboBox::currentTextChanged, this, &UIValue::onComboBoxCurrentTextChanged);

                    m_widget = widget;

                } else {
                    auto *widget = new QCheckBox();
                    widget->setText("");
                    widget->setChecked(m_ref.toBool());
                    ui->verticalLayout_Value->addWidget(widget);
                    widget->setToolTip(description);

                    connect(widget, &QCheckBox::stateChanged, this, &UIValue::onBoolChanged);

                    m_widget = widget;
                }
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
        emit changed(m_key, this);

    }

    void UIValue::onNumberTextChanged(const QString &text) {
        qDebug() << "UIValue::onNumberTextChanged()";
        m_ref = text.toDouble();
        qDebug() << "m_ref:" << m_ref;
        emit changed(m_key, this);
    }

    void UIValue::onNumberSelectChanged(double value) {
        qDebug() << "UIValue::onNumberSelectChanged()";
        m_ref = value;
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

    void UIValue::onArrayChanged(QString key, UIArray *uiArray) {
        qDebug() << "UIValue::onArrayChanged()";
        m_ref = uiArray->getArray();
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

    void UIValue::onComboBoxCurrentTextChanged(const QString &text){
        qDebug() << "UIValue::onComboBoxCurrentTextChanged()";
        auto widget = (QComboBox *)m_widget;

        if (m_ref.isDouble()) {
            m_ref = widget->currentData().toDouble();
        } else if (m_ref.isBool()) {
            m_ref = widget->currentData().toBool();
        } else {
            m_ref = widget->currentData().toString();
        }
        emit changed(m_key, this);
    }
} // fairwind::apps::settings::browser
