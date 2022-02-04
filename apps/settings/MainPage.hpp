//
// Created by __author__ on 18/01/2022.
//

#ifndef SETTINGS_MAINPAGE_HPP
#define SETTINGS_MAINPAGE_HPP

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/PageBase.hpp>
#include <FairWindSdk/FairWindApp.hpp>

#include "ui_MainPage.h"

namespace fairwind::apps::settings {
    QT_BEGIN_NAMESPACE
    namespace Ui { class General; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::apps::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(QWidget *parent = nullptr, FairWindApp *fairWindApp = nullptr);

        ~MainPage() ;

    private:
        Ui::MainPage *ui;
    };
} // fairwind::apps::settings

#endif //SETTINGS_MAINPAGE_HPP
