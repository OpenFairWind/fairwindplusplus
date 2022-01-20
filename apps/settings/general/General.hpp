//
// Created by Raffaele Montella on 19/01/22.
//

#ifndef FAIRWIND_APPS_SETTINGS_GENERAL_GENERAL_HPP
#define FAIRWIND_APPS_SETTINGS_GENERAL_GENERAL_HPP

#include <QWidget>
#include <FairWindSdk/ISettingsTab.hpp>
#include <QJsonObject>

#include "../browser/Browser.hpp"

namespace fairwind::apps::settings::general {
    QT_BEGIN_NAMESPACE
    namespace Ui { class General; }
    QT_END_NAMESPACE

    class General : public QWidget, public ui::settings::ISettingsTab {
    Q_OBJECT

    public:
        explicit General(QWidget *parent = nullptr);

        ~General() override;


        QString getClassName() const override;

        QImage getIcon() const override;

        QString getName() const override;

        ISettingsTab *getNewInstance() override;

        void setJsonObjectRoot(QJsonObject jsonObjectRoot);
        QJsonObject getJsonObjectRoot();

    protected :
        void showEvent(QShowEvent *event) override;

    private:
        Ui::General *ui;

        browser::Browser *mBrowser;
        QJsonObject m_config;

    };
} // fairwind::apps::settings::general

#endif //FAIRWIND_APPS_SETTINGS_GENERAL_GENERAL_HPP
