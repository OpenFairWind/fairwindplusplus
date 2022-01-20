//
// Created by Raffaele Montella on 19/01/22.
//

#ifndef FAIRWIND_APPS_SETTINGS_BROWSER_BROWSER_HPP
#define FAIRWIND_APPS_SETTINGS_BROWSER_BROWSER_HPP

#include <QWidget>
#include "UIObject.hpp"

namespace fairwind::apps::settings::browser {
    QT_BEGIN_NAMESPACE
    namespace Ui { class Browser; }
    QT_END_NAMESPACE

    class Browser : public QWidget {
    Q_OBJECT

    public:
        explicit Browser(QWidget *parent = nullptr);

        ~Browser() override;

        void setJsonObjectRoot(QJsonObject jsonObjectRoot);
        QJsonObject getJsonObjectRoot();

    private:
        Ui::Browser *ui;

        QVector<UIObject *> m_items;
        QJsonObject m_jsonObjectRoot;
    };
} // fairwind::apps::settings::browser

#endif //FAIRWIND_APPS_SETTINGS_BROWSER_BROWSER_HPP
