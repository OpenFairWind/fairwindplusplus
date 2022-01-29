//
// Created by Raffaele Montella on 22/01/22.
//

#ifndef FAIRWIND_UIVALUE_HPP
#define FAIRWIND_UIVALUE_HPP

#include <QWidget>
#include <QJsonValueRef>
#include <QJsonObject>
#include "UIObject.hpp"

namespace fairwind::apps::settings::browser {
    QT_BEGIN_NAMESPACE
    namespace Ui { class UIValue; }
    QT_END_NAMESPACE

    class UIObject;
    class UIArray;
    class UIValue : public QWidget {
    Q_OBJECT

    public:
        explicit UIValue(QWidget *parent, ExtendedJsonSchema *settings, QJsonValueRef ref, QString path);

        ~UIValue() override;

        QJsonValueRef getValue();

    signals:

        void changed(QString key, UIValue *uiValue);

    public slots:

        void onTextChanged();

        void onNumberTextChanged(const QString &text);

        void onNumberSelectChanged(double value);

        void onBoolChanged(int state);

        void onArrayChanged(QString key, UIArray *uiArray);

        void onObjectChanged(QString key, UIObject *uiObject);

        void onComboBoxCurrentTextChanged(const QString &text);

    private:
        QJsonValueRef m_ref;
        QString m_key;
        QWidget *m_widget;
        Ui::UIValue *ui;
    };
} // fairwind::apps::settings::browser

#endif //FAIRWIND_UIVALUE_HPP
