//
// Created by Raffaele Montella on 12/04/21.
//

#ifndef FAIRWIND_TOPBAR_HPP
#define FAIRWIND_TOPBAR_HPP

#include <QWidget>
#include <FairWindSdk/FairWind.hpp>

namespace Ui {
    class TopBar;
}

namespace fairwind::ui::topbar {
    class TopBar : public QWidget {
    Q_OBJECT
    public:
        explicit TopBar(QWidget *parent = 0);

        ~TopBar();

        void setFairWindApp(AppItem *appItem);

    public slots:
        void toolbuttonUL_clicked();
        void toolbuttonUR_clicked();

    public slots:

        void updateNavigationPosition(const QJsonObject update);

        void updateNavigationCourseOverGroundTrue(const QJsonObject update);

        void updateNavigationSpeedOverGround(const QJsonObject update);

        void updateTime();

        signals:
        void clickedToolbuttonUL();
        void clickedToolbuttonUR();

    private:
        Ui::TopBar *ui;
        AppItem *mAppItem;
    };
}

#endif //FAIRWIND_TOPBAR_HPP