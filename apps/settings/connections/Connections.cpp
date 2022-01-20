//
// Created by Raffaele Montella on 16/07/21.
//

#include <QTableWidgetItem>

#include <FairWindSdk/FairWind.hpp>

#include "Connections.hpp"
#include "ui_Connections.h"

namespace fairwind::apps::settings::connections {
/*
 * Connections
 * Public constructor - This presents the connections related settings inside a tab
 */
    Connections::Connections(QWidget *parent) :
            QWidget(parent),
            ui(new Ui::Connections) {

        // Setup the UI
        ui->setupUi(this);

        // Get the table containing the connections list from the UI
        auto tableConnectionList = ui->table_ConnectionsList;
        // Set the table to have two columns
        tableConnectionList->setColumnCount(2);
        // Set the columns labels
        QStringList connectionsLabels;
        connectionsLabels.append(tr("Name"));
        connectionsLabels.append(tr("Label"));

        // Set a new header with the labels
        tableConnectionList->setHorizontalHeaderLabels(connectionsLabels);
        // Set the new header resize mode to stretch on UI change
        tableConnectionList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

/*
 * ~Connections
 * Connections' destructor
 */
    Connections::~Connections() {
        delete ui;
    }

/*
 * showEvent
 * Method called when the tab has to be shown
 */
    void Connections::showEvent(QShowEvent *event) {
        qDebug() << "fairwind::apps::settings::connections::Connections::showEvent";

        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();

        // Get the connections list from the FairWind singleton itself
        auto connectionsList = fairWind->getConnectionsList();

        // Get the table containing the connections list from the UI
        auto tableConnectionList = ui->table_ConnectionsList;

        // Remove every row
        while (tableConnectionList->rowCount() > 0) {
            tableConnectionList->removeRow(0);
        }

        // Iterate on the available connections
        for (auto connection: *connectionsList) {
            // Get the row count from the table
            int row = tableConnectionList->rowCount();
            // Add a new row at the end
            tableConnectionList->insertRow(row);
            // Create a new item with the name of the connection
            auto itemIcon = new QTableWidgetItem(connection->getName());
            itemIcon->data(Qt::CheckStateRole);
            // Check if the connection is active
            bool active = connection->isActive();
            // Check or uncheck the new item accordingly
            if (active) {
                itemIcon->setCheckState(Qt::Checked);
            } else {
                itemIcon->setCheckState(Qt::Unchecked);
            }

            // Set the connection's icon as the new item's icon
            itemIcon->setIcon(QIcon(QPixmap::fromImage(connection->getIcon())));

            // Add the new item to the table
            tableConnectionList->setItem(row, 0, itemIcon);

            // Get the connection label
            QString label = connection->getLabel();
            qDebug() << "Settings::onCurrentWidget :" << active << " , " << label;
            // Add a new item to the table containing the connection label
            tableConnectionList->setItem(row, 1, new QTableWidgetItem(label));
        }

        // Continue with the regular showEvent
        QWidget::showEvent(event);
    }

/*
 * getIcon
 * Returns a QImage containing the connections' settings icon
 */
    QImage Connections::getIcon() const {
        return QImage(":resources/images/icons/connections_icon.png");
    }

/*
 * getName
 * Returns a string containing the connections' settings name
 */
    QString Connections::getName() const {
        return tr("Connections");
    }

/*
 * getNewInstance
 * Returns a new instance of Connections
 */
    fairwind::ui::settings::ISettingsTab *Connections::getNewInstance() {
        return static_cast<ISettingsTab *>(new Connections());
    }

/*
 * getClassName
 * Returns the current Connections instance class name
 */
    QString Connections::getClassName() const {
        return this->metaObject()->className();
    }
}