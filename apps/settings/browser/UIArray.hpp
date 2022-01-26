//
// Created by Raffaele Montella on 10/01/22.
//

#ifndef FAIRWIND_APPS_SETTINGS_BROWSER_UIARRAY_HPP
#define FAIRWIND_APPS_SETTINGS_BROWSER_UIARRAY_HPP

#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
#include "UIItem.hpp"

namespace fairwind::apps::settings::browser {
    QT_BEGIN_NAMESPACE
    namespace Ui { class UIArray; }
    QT_END_NAMESPACE

    class UIArray : public QWidget {
    Q_OBJECT

    public:
        explicit UIArray(QWidget *parent, ExtendedJsonSchema *settings, QJsonValueRef mRef, QString path);

        ~UIArray() override;

        QJsonValueRef getArray();

    signals:

        void changed(QString key, UIArray *uiArray);

    public slots:

        void onChanged();

        void onAdd();

    private:
        Ui::UIArray *ui;
        QJsonValueRef m_ref;
        QString m_key;
        QJsonArray m_jsonArray;
        QVector<UIItem *> m_uiItems;
        ExtendedJsonSchema *m_settings;
        QString m_path;

    };
}

#endif //FAIRWIND_APPS_SETTINGS_BROWSER_UIARRAY_HPP
