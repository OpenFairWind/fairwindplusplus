//
// Created by __author__ on 18/01/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <FairWindSdk/PageBase.hpp>

#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::settings {
    MainPage::MainPage(PageBase *parent) :
            PageBase(parent), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);

        // Get the singleton instance of FairWind
        FairWind *fairWind = FairWind::getInstance();

        // Get the registered settings pages from the FairWind instance itself
        for (const auto settings: *(fairWind->getSettingsList())) {
            // Add a new tab for each page
            ui->tabWidget->addTab(dynamic_cast<QWidget *>(settings), settings->getName());
        }
    }

    MainPage::~MainPage() {
        delete ui;
    }
} // fairwind::apps::settings
