//
// Created by __author__ on __date__.
//

#ifndef __APPNAME___MAINPAGE_HPP
#define __APPNAME___MAINPAGE_HPP

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/PageBase.hpp>
#include <FairWindSdk/FairWindApp.hpp>

#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace __namespace__ {
    QT_BEGIN_NAMESPACE
    namespace Ui { class MainPage; }
    QT_END_NAMESPACE

    class MainPage : public fairwind::apps:::PageBase {
    Q_OBJECT

    public:
        explicit MainPage(PageBase *parent = nullptr);

        ~MainPage() ;

        void onAdded() override;

    private:
        Ui::MainPage *ui;
    };
} // __namespace__

#endif //__APPNAME___MAINPAGE_HPP
