//
// Created by __author__ on __date__.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <FairWindSdk/PageBase.hpp>

#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace __namespace__ {
    MainPage::MainPage(QWidget *parent, FairWindApp *fairWindApp) :
            PageBase(parent, fairWindApp), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);
    }

    MainPage::~MainPage() {
        delete ui;
    }
} // __namespace__
