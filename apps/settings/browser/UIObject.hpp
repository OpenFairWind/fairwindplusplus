//
// Created by Raffaele Montella on 09/01/22.
//

#ifndef FAIRWIND_APPS_SETTINGS_BROWSER_UIOBJECT_HPP
#define FAIRWIND_APPS_SETTINGS_BROWSER_UIOBJECT_HPP

#include <QWidget>
#include <QJsonObject>

namespace fairwind::apps::settings::browser {
    QT_BEGIN_NAMESPACE
    namespace Ui { class UIObject; }
    QT_END_NAMESPACE

    class UIObject : public QWidget {
    Q_OBJECT

    public:
        explicit UIObject(QWidget *parent, QJsonValueRef ref, QString key);

        ~UIObject() override;

    signals:

        void changed();

    public slots:

        void onTextChanged();

        void onNumberChanged();

        void onArrayChanged();

        void onStateChanged(int state);


    private:
        QJsonValueRef m_ref;
        QString m_key;
        QWidget *m_widget;

        Ui::UIObject *ui;
    };

}
#endif //FAIRWIND_APPS_SETTINGS_BROWSER_UIOBJECT_HPP
