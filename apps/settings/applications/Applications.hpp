//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_APPS_SETTINGS_APPLICATIONS_HPP
#define FAIRWIND_APPS_SETTINGS_APPLICATIONS_HPP


#include <QItemSelection>

#include <FairWindSdk/ISettingsTab.hpp>

namespace Ui {
    class Applications;
}

namespace fairwind::apps::settings::applications {
    class Applications : public QWidget, public ui::settings::ISettingsTab {
        Q_OBJECT

    public:
        explicit Applications(QWidget *parent = 0);

        ~Applications();

        QString getClassName() const override;

        QImage getIcon() const override;

        QString getName() const override;

        ISettingsTab *getNewInstance() override;

    protected :
        void showEvent(QShowEvent *event) override;

    private
        slots:
                void onCurrentRowChanged(
        const QModelIndex &current,
        const QModelIndex &previous
        );

    private:
        Ui::Applications *ui;

        QString mExtension;
        QMap<QString, QWidget *> mSettingsByExtensionId;
    };
}

#endif //FAIRWIND_APPS_SETTINGS_APPLICATIONS_HPP