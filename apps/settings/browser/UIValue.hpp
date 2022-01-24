//
// Created by Raffaele Montella on 22/01/22.
//

#ifndef FAIRWIND_UIVALUE_HPP
#define FAIRWIND_UIVALUE_HPP

#include <QWidget>
#include <QJsonValueRef>
#include <QJsonObject>

namespace fairwind::apps::settings::browser {
    QT_BEGIN_NAMESPACE
    namespace Ui { class UIValue; }
    QT_END_NAMESPACE

    class UIValue : public QWidget {
    Q_OBJECT

    public:
        explicit UIValue(QWidget *parent, QJsonValueRef ref, QString key);

        ~UIValue() override;

    signals:

        void changed();

    public slots:

        void onTextChanged();

        void onNumberChanged();

        void onBoolChanged(int state);

        void onArrayChanged();
        void onObjectChanged();

    private:
        QJsonValueRef m_ref;
        QString m_key;
        QWidget *m_widget;

        Ui::UIValue *ui;
    };
} // fairwind::apps::settings::browser

#endif //FAIRWIND_UIVALUE_HPP
