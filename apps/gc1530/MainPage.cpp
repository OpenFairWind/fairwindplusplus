//
// Created by Raffaele Montella on 13/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <QPushButton>
#include "MainPage.hpp"
#include "ui_MainPage.h"
#include "GC1530.hpp"


namespace it::gov::guardiacostiera::gc1530 {
    MainPage::MainPage(PageBase *parent) :
            PageBase(parent), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);

        m_webView = new WebView((QWidget *)this);
        m_webView->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        ui->verticalLayout_WebView->addWidget(m_webView);
        connect(ui->pushButton_Home, &QPushButton::clicked, this, &::it::gov::guardiacostiera::gc1530::MainPage::toolButton_home_clicked);


    }

    void MainPage::onAdded() {
        m_webView->load(QUrl(((GC1530 *)getFairWindApp())->getHomeUrl()));
    }


    MainPage::~MainPage() {
        delete ui;
    }

    void MainPage::toolButton_home_clicked() {
        GC1530 *fairWindApp = (GC1530 *)getFairWindApp();
        QString homeUrl = fairWindApp->getHomeUrl();
        qDebug() << "homeUrl: " << homeUrl;
        m_webView->load(homeUrl);
    }
} // it::gov::guardiacostiera::gc1530
