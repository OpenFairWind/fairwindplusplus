//
// Created by Raffaele Montella on 14/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainPage.h" resolved

#include <FairWindSdk/PageBase.hpp>
#include <QComboBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonArray>

#include "MainPage.hpp"
#include "ui_MainPage.h"
#include "ResultItem.hpp"
#include "Portolano.hpp"

namespace fairwind::apps::portolano {
    MainPage::MainPage(QWidget *parent, FairWindApp *fairWindApp) :
            PageBase(parent, fairWindApp), ui(new Ui::MainPage) {

        ui->setupUi((QWidget *)this);

        connect(ui->comboBox_Search,&QComboBox::editTextChanged,this,&MainPage::onEditTextChanged);
    }

    MainPage::~MainPage() {
        delete ui;
    }


    void MainPage::onEditTextChanged(const QString &text) {

        auto *fairWindApp = (Portolano *)getFairWindApp();
        auto db = fairWindApp->getDb();
        if (db->open()) {

            QSqlQuery query(*db);
            QString q = QString("SELECT * FROM ports WHERE name LIKE \"%%1%\" LIMIT 10;").arg(text);
            query.prepare(q);
            query.exec();

            ui->listWidget_Results->clear();
            while (query.next()) {
                QString strJsonFeature = query.value(4).toString();
                QJsonDocument doc = QJsonDocument::fromJson(strJsonFeature.toLatin1());
                auto widget = new ResultItem(ui->listWidget_Results, doc.object());
                widget->setMinimumWidth(150);

                auto listWidgetItem = new QListWidgetItem();
                listWidgetItem->setSizeHint(widget->sizeHint());

                ui->listWidget_Results->addItem(listWidgetItem);
                ui->listWidget_Results->setItemWidget(listWidgetItem, widget);

            }

        }
    }
} // fairwind::appls::portolano
