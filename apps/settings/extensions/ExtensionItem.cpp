//
// Created by Raffaele Montella on 23/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ExtensionItem.h" resolved

#include "ExtensionItem.hpp"
#include "ui_ExtensionItem.h"

namespace fairwind::apps::settings::extensions {
    ExtensionItem::ExtensionItem(QWidget *parent, IFairWindApp *fairWindApp) :
            QWidget(parent), ui(new Ui::ExtensionItem), mFairWindApp(fairWindApp) {
        ui->setupUi(this);

        if (mFairWindApp) {

            ui->label_Name->setText(mFairWindApp->getName());
            ui->label_Version->setText(mFairWindApp->getVersion());
            ui->label_Category->setText(mFairWindApp->getCategory());
            ui->toolButton_Icon->setIcon(QPixmap::fromImage(mFairWindApp->getIcon()));
        }
    }

    ExtensionItem::~ExtensionItem() {
        delete ui;
    }

    IFairWindApp *ExtensionItem::getFairWindApp() {
        return mFairWindApp;
    }
} // fairwind::apps::settings::extensions
