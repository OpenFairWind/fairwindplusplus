//
// Created by Raffaele Montella on 16/07/21.
//

#include <QTableWidgetItem>
#include <FairWindSdk/FairWind.hpp>
#include "Applications.hpp"
#include "ui_Applications.h"

fairwind::ui::settings::applications::Applications::Applications(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Applications) {
    ui->setupUi(this);

    auto tableAppsList = ui->table_AppsList;
    tableAppsList->setColumnCount(1);
    QStringList appsLabels;
    appsLabels.append(tr("Name"));

    tableAppsList->setHorizontalHeaderLabels(appsLabels);
    tableAppsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

fairwind::ui::settings::applications::Applications::~Applications() {
    delete ui;
}

void fairwind::ui::settings::applications::Applications::showEvent(QShowEvent *event) {

    auto fairWind = fairwind::FairWind::getInstance();

    auto apps = fairWind->getApps();

    auto tableAppsList = ui->table_AppsList;

    while (tableAppsList->rowCount()>0) {
        tableAppsList->removeRow(0);
    }

    for (auto app:apps) {
        int row  = tableAppsList->rowCount();
        tableAppsList->insertRow( row );
        auto itemIcon = new QTableWidgetItem(
                app->getName()+"\n" +
                app->getDesc()+"\n"
                );
        itemIcon->data(Qt::CheckStateRole);
        bool active=app->getActive();
        if (active) {
            itemIcon->setCheckState(Qt::Checked);
        } else {
            itemIcon->setCheckState(Qt::Unchecked);
        }

        itemIcon->setIcon(QIcon(QPixmap::fromImage(app->getIcon())));

        tableAppsList->setItem( row, 0, itemIcon);
    }

    QWidget::showEvent(event);
}

QImage fairwind::ui::settings::applications::Applications::getIcon() const {
    return QImage(":resources/images/icons/applications_icon.png");
}

QString fairwind::ui::settings::applications::Applications::getName() const {
    return tr("Applications");
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::applications::Applications::getNewInstance() {
    return static_cast<ISettings *>(new Applications());
}

QString fairwind::ui::settings::applications::Applications::getClassName() const {
    return this->metaObject()->className();
}

