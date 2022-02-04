//
// Created by __author__ on 21/01/2022.
//

#ifndef LAUNCHERAX10M_MAINPAGE_HPP
#define LAUNCHERAX10M_MAINPAGE_HPP

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/PageBase.hpp>
#include <FairWindSdk/FairWindApp.hpp>

#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::launcherax10m {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainPage; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::apps::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(QWidget *parent = nullptr, FairWindApp *fairWindApp = nullptr);

        ~MainPage() ;

        void toolButton_App_released();

    signals:

        void foregroundAppChanged(const QString hash);

    private:
        Ui::MainPage *ui;
    };
} // fairwind::apps::launcherax10m

#endif //LAUNCHERAX10M_MAINPAGE_HPP
