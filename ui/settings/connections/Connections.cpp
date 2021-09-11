//
// Created by Raffaele Montella on 16/07/21.
//

#include <QTableWidgetItem>
#include <FairWindSdk/FairWind.hpp>
#include "Connections.hpp"
#include "ui_Connections.h"

fairwind::ui::settings::connections::Connections::Connections(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Connections) {

    ui->setupUi(this);

    auto tableConnectionList = ui->table_ConnectionsList;
    tableConnectionList->setColumnCount(2);
    QStringList connectionsLabels;
    connectionsLabels.append(tr("Name"));
    connectionsLabels.append(tr("Label"));

    tableConnectionList->setHorizontalHeaderLabels(connectionsLabels);
    tableConnectionList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

fairwind::ui::settings::connections::Connections::~Connections() {
    delete ui;
}

void fairwind::ui::settings::connections::Connections::showEvent(QShowEvent *event) {
    qDebug() << "fairwind::ui::settings::connections::Connections::showEvent";

    auto fairWind = fairwind::FairWind::getInstance();

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
    QWidget::showEvent(event);
}

QImage fairwind::ui::settings::connections::Connections::getIcon() const {
    return QImage(":resources/images/icons/connections_icon.png");
}

QString fairwind::ui::settings::connections::Connections::getName() const {
    return tr("Connections");
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::connections::Connections::getNewInstance() {
    return static_cast<ISettings *>(new Connections());
}

QString fairwind::ui::settings::connections::Connections::getClassName() const {
    return this->metaObject()->className();
}