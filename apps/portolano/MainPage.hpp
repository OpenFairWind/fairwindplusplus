//
// Created by Raffaele Montella on 14/01/22.
//

#ifndef FAIRWIND_MAINPAGE_HPP
#define FAIRWIND_MAINPAGE_HPP

#include <QDebug>
#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/PageBase.hpp>
#include <FairWindSdk/FairWindApp.hpp>

#include <utility>
#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::portolano {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainPage; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(QWidget *parent = nullptr, FairWindApp *fairWindApp = nullptr);

        ~MainPage() ;

    private:
        Ui::MainPage *ui;
    };
} // fairwind::appls::portolano

#endif //FAIRWIND_MAINPAGE_HPP
