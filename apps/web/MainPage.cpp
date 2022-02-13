//
// Created by Raffaele Montella on 14/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <QPushButton>
#include <FairWindSdk/FairWindApp.hpp>
#include "MainPage.hpp"
#include "ui_MainPage.h"

namespace fairwind::apps::web {
    MainPage::MainPage(PageBase *parent) :
            PageBase(parent), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);



        m_webView = new WebView((QWidget *)this);
        m_webView->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        ui->verticalLayout_WebView->addWidget(m_webView);
        connect(ui->pushButton_Home, &QPushButton::clicked, this, &MainPage::toolButton_home_clicked);


    }

    void MainPage::onAdded() {
        auto args = getFairWindApp()->getArgs();
        if (args.contains("Url")) {
            m_url = args["Url"].toString();
        }
        m_webView->load(QUrl(m_url));
    }

    MainPage::~MainPage() {
        delete ui;
    }

    void MainPage::toolButton_home_clicked() {
        m_webView->load(m_url);
    }
} // fairwind::apps::web
