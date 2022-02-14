//
// Created by Raffaele Montella on 19/01/22.
//

#ifndef FAIRWIND_APPS_SETTINGS_BROWSER_BROWSER_HPP
#define FAIRWIND_APPS_SETTINGS_BROWSER_BROWSER_HPP

#include <QWidget>
#include <FairWindSdk/util/ExtendedJsonSchema.hpp>
#include "UIObject.hpp"
#include "UIValue.hpp"

namespace fairwind::apps::settings::browser {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Browser; }
    QT_END_NAMESPACE

    class Browser : public QWidget {
    Q_OBJECT

    public:
        explicit Browser(QWidget *parent = nullptr);

        ~Browser() override;

        void setJsonObjectRoot(ExtendedJsonSchema *settings, QJsonObject jsonObjectRoot);
        QJsonObject getJsonObjectRoot();

    signals:

        void changed();

    public slots:
        void onChanged(QString key, UIValue *uiValue);

    private:
        Ui::Browser *ui;

        QVector<UIValue *> m_uiValues;
        QJsonObject m_jsonObjectRoot;
        ExtendedJsonSchema *m_settings;
    };
} // fairwind::apps::settings::browser

#endif //FAIRWIND_APPS_SETTINGS_BROWSER_BROWSER_HPP
