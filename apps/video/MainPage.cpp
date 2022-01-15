//
// Created by Raffaele Montella on 15/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::video {
    MainPage::MainPage(QWidget *parent, FairWindApp *fairWindApp) :
            PageBase(parent, fairWindApp), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);
    }

    MainPage::~MainPage() {
        delete ui;
    }
} // fairwind::apps::video
