//
// Created by Raffaele Montella on 13/04/21.
//

#include <FairWindSdk/FairWind.hpp>
#include <QTableWidgetItem>
#include "Settings.hpp"
#include "ui_Settings.h"


fairwind::ui::settings::Settings::Settings(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Settings) {

    ui->setupUi(this);

    auto tableConnectionList = ui->table_ConnectionsList;
    tableConnectionList->setColumnCount(2);
    QStringList connectionsLabels;
    connectionsLabels.append(tr("Name"));
    connectionsLabels.append(tr("Label"));

    tableConnectionList->setHorizontalHeaderLabels(connectionsLabels);
    tableConnectionList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto tableAppsList = ui->table_AppsList;
    tableAppsList->setColumnCount(1);
    QStringList appsLabels;
    appsLabels.append(tr("Name"));

    tableAppsList->setHorizontalHeaderLabels(appsLabels);
    tableAppsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

fairwind::ui::settings::Settings::~Settings() {
    delete ui;
}

void fairwind::ui::settings::Settings::showEvent(QShowEvent *e)
{
    auto fairWind=fairwind::FairWind::getInstance();
    auto connectionsList = fairWind->getConnectionsList();

    auto tableConnectionList = ui->table_ConnectionsList;

    while (tableConnectionList->rowCount()>0) {
        tableConnectionList->removeRow(0);
    }

    for (auto connection:*connectionsList) {
        int row  = tableConnectionList->rowCount();
        tableConnectionList->insertRow( row );
        auto itemIcon = new QTableWidgetItem(connection->getName());
        itemIcon->data(Qt::CheckStateRole);
        bool active=connection->isActive();
        if (active) {
            itemIcon->setCheckState(Qt::Checked);
        } else {
            itemIcon->setCheckState(Qt::Unchecked);
        }

        itemIcon->setIcon(QIcon(QPixmap::fromImage(connection->getIcon())));

        tableConnectionList->setItem( row, 0, itemIcon);

        QString label=connection->getLabel();
        qDebug() << "Settings::onCurrentWidget :" << active << " , " << label;
        tableConnectionList->setItem( row, 1, new QTableWidgetItem(label));

    }

    auto apps = fairWind->getApps();

    auto tableAppsList = ui->table_AppsList;

    while (tableAppsList->rowCount()>0) {
        tableAppsList->removeRow(0);
    }

    for (auto app:apps) {
        int row  = tableAppsList->rowCount();
        tableAppsList->insertRow( row );
        auto itemIcon = new QTableWidgetItem(app->getName());
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
}
