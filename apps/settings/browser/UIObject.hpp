//
// Created by Raffaele Montella on 09/01/22.
//

#ifndef FAIRWIND_APPS_SETTINGS_BROWSER_UIOBJECT_HPP
#define FAIRWIND_APPS_SETTINGS_BROWSER_UIOBJECT_HPP

#include <QWidget>
#include <QJsonObject>
#include "UIValue.hpp"


namespace fairwind::apps::settings::browser {
    QT_BEGIN_NAMESPACE
    namespace Ui { class UIObject; }
    QT_END_NAMESPACE

    class UIValue;
    class UIObject : public QWidget {
    Q_OBJECT

    public:
        explicit UIObject(QWidget *parent, ExtendedJsonSchema *settings, QJsonValueRef ref, QString path);

        ~UIObject() override;

        QJsonValueRef getObject();

    signals:

        void changed(QString key, UIObject *uiObject);

    public slots:
        void onChanged(QString key, UIValue *uiValue);
        void onAdd();

    private:
        QJsonValueRef m_ref;
        QString m_key;
        QWidget *m_widget;
        QJsonObject m_jsonObject;
        QMap<QString, UIValue *> m_mapUiValues;
        Ui::UIObject *ui;
    };

}
#endif //FAIRWIND_APPS_SETTINGS_BROWSER_UIOBJECT_HPP
