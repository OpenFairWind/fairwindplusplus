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

    // Setup the user interface
    ui->setupUi(this);

    // Get the table AppsList
    auto tableAppsList = ui->table_AppsList;

    // Set the table with one single column
    tableAppsList->setColumnCount(1);

    // Prepare the header labels
    QStringList appsLabels;
    appsLabels.append(tr("Name"));

    // Set the horizontal headers
    tableAppsList->setHorizontalHeaderLabels(appsLabels);

    // Set the resize mode
    tableAppsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(tableAppsList->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &Applications::onCurrentRowChanged);
}

fairwind::ui::settings::applications::Applications::~Applications() {
    delete ui;
}

/*
 * showEvent : called when the tab have to be shown
 */
void fairwind::ui::settings::applications::Applications::showEvent(QShowEvent *event) {

    // The the FairWind singleton instance
    auto fairWind = fairwind::FairWind::getInstance();

    // Get the applications list
    auto apps = fairWind->getApps();

    // Get the table ApplsList
    auto tableAppsList = ui->table_AppsList;

    // While the number of rows is greater than zero
    while (tableAppsList->rowCount()>0) {

        // Remove the row
        tableAppsList->removeRow(0);
    }

    // For each app
    for (auto app:apps) {

        // Get the row count
        int row  = tableAppsList->rowCount();

        // Add a new row
        tableAppsList->insertRow( row );

        // Create the item icon
        auto itemIcon = new QTableWidgetItem(
                app->getName()+"\n" +
                app->getDesc()+"\n"
                );

        // Set the item as checkbox
        itemIcon->data(Qt::CheckStateRole);

        // Get the app status (active: true|false)
        bool active=app->getActive();

        // Check if the app is active
        if (active) {

            // Set the checkbox as active
            itemIcon->setCheckState(Qt::Checked);

        } else {

            // Else set the checkbox as not active
            itemIcon->setCheckState(Qt::Unchecked);
        }

        // Set the item icon as the app icon
        itemIcon->setIcon(QIcon(QPixmap::fromImage(app->getIcon())));

        // Add the row to the table AppsList
        tableAppsList->setItem( row, 0, itemIcon);
    }

    // Continue with the regular show event
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


void fairwind::ui::settings::applications::Applications::onCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous) {
    // The the FairWind singleton instance
    auto fairWind = fairwind::FairWind::getInstance();

    // Get the applications list
    auto apps = fairWind->getApps();

    if(previous.isValid()) {
        qDebug() << "Previous:" << previous.row();
        ui->scrollArea_Apps->takeWidget();
    }
    qDebug() << "Current:" << current.row();

    // Get the application unique key by index
    auto key = apps.keys().at(current.row());

    // Get the reference to the application
    auto app = apps[key];


    // Get the extension reference by the application id
    auto extension = fairWind->getAppByExtensionId(app->getExtension());
    auto widget = extension->onSettings(nullptr);

    ui->scrollArea_Apps->setWidget(widget);
}

