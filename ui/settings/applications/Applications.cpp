//
// Created by Raffaele Montella on 16/07/21.
//

#include <QTableWidgetItem>
#include <FairWindSdk/FairWind.hpp>

#include "Applications.hpp"
#include "ui_Applications.h"
#include "QJsonArray"
#include "QComboBox"
#include "QCheckBox"
#include "QLineEdit"
#include "QLabel"

/*
 * Applications
 * Public constructor - This will present the available apps in FairWind
 */
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

    // Update the UI when the current changes
    connect(tableAppsList->selectionModel(), &QItemSelectionModel::currentRowChanged, this,
            &Applications::onCurrentRowChanged);
}

/*
 * ~Applications
 * Applications' destructor
 */
fairwind::ui::settings::applications::Applications::~Applications() {
    delete ui;
}

/*
 * showEvent
 * Method called when the tab has to be showed
 */
void fairwind::ui::settings::applications::Applications::showEvent(QShowEvent *event) {
    qDebug() << "fairwind::ui::settings::applications::Applications::showEvent";

    // Get the FairWind singleton instance
    auto fairWind = fairwind::FairWind::getInstance();

    // Get the applications list
    auto apps = fairWind->getApps();

    // Get the table AppsList
    auto tableAppsList = ui->table_AppsList;

    // Remove all items
    tableAppsList->setRowCount(0);

    // For each app
    for (auto app: apps) {
        // Get the row count
        int row = tableAppsList->rowCount();

        // Add a new row
        tableAppsList->insertRow(row);

        // Create the item icon
        auto itemIcon = new QTableWidgetItem(
                app->getName() + "\n" +
                app->getDesc() + "\n"
        );

        // Set the item as checkbox
        itemIcon->data(Qt::CheckStateRole);

        // Get the app status (active: true|false)
        bool active = app->getActive();

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
        tableAppsList->setItem(row, 0, itemIcon);
    }

    // Continue with the regular showEvent
    QWidget::showEvent(event);
}

/*
 * getIcon
 * Returns a QImage containing the applications' settings icon
 */
QImage fairwind::ui::settings::applications::Applications::getIcon() const {
    return QImage(":resources/images/icons/applications_icon.png");
}

/*
 * getName
 * Returns a string containing the applications' settings name
 */
QString fairwind::ui::settings::applications::Applications::getName() const {
    return tr("Applications");
}

/*
 * getNewInstance
 * Returns a new instance of Applications
 */
fairwind::ui::settings::ISettingsTab *fairwind::ui::settings::applications::Applications::getNewInstance() {
    return static_cast<ISettingsTab *>(new Applications());
}

/*
 * getClassName
 * Returns the current Applications instance class name
 */
QString fairwind::ui::settings::applications::Applications::getClassName() const {
    return this->metaObject()->className();
}

/*
 * onCurrentChanged
 * Method called when the row is changed
 */
void fairwind::ui::settings::applications::Applications::onCurrentRowChanged(const QModelIndex &current,
                                                                             const QModelIndex &previous) {
    qDebug() << "fairwind::ui::settings::applications::Applications::onCurrentRowChanged";

    // The FairWind singleton instance
    auto fairWind = fairwind::FairWind::getInstance();

    // Get the applications list
    auto apps = fairWind->getApps();

    if (previous.isValid()) {
        qDebug() << "Previous:" << previous.row();
        ui->scrollArea_Apps->takeWidget();
    }
    qDebug() << "Current:" << current.row();

    // Check if a current row is selected
    if (current.row() >= 0) {

        // Get the application unique key by index
        auto key = apps.keys().at(current.row());

        // Get the reference to the application
        auto app = apps[key];

        // Store the extension id
        mExtension = app->getExtension();
    }

    // Get the extension reference by the application id
    auto extension = fairWind->getAppByExtensionId(mExtension);

    auto configs = extension->getConfig();

    auto tableAppsList = new QTableWidget;
    tableAppsList->setColumnCount(1);
    tableAppsList->setRowCount(0);
    tableAppsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableAppsList->horizontalHeader()->setVisible(false);
    tableAppsList->verticalHeader()->setVisible(false);

    auto settings = configs["Settings"].toArray();
    auto values = configs["Values"].toObject();

    for (int i = 0; i < settings.size(); i++) {
        auto widget = fairWind->instanceSettings(settings[i].toObject()["widgetClassName"].toString());

        if (widget != nullptr) {
            auto label = new QLabel(settings[i].toObject()["displayName"].toString() + ":");

            tableAppsList->insertRow(tableAppsList->rowCount());
            tableAppsList->setCellWidget(tableAppsList->rowCount() - 1, 0, label);

            widget->setDetails(settings[i].toObject(), values, extension);

            tableAppsList->insertRow(tableAppsList->rowCount());
            tableAppsList->setCellWidget(tableAppsList->rowCount() - 1, 0, dynamic_cast<QWidget *>(widget));
        }
    }

    /*for (int i = 0; i < settings.size(); i++ ) {

        if (widgetClassName == "QLineEdit") {
            auto line = new QLineEdit;
            line->setText(values[settingsID].toString());

            connect(line,static_cast<void (QLineEdit::*)(const QString& newValue)>(&QLineEdit::textChanged), this, [settingsID, extension](QString newValue) {
                extension->updateSettings(settingsID, newValue);
            });

            // Add a new row
            tableAppsList->insertRow(tableAppsList->rowCount());
            tableAppsList->setCellWidget(tableAppsList->rowCount() - 1, 0, line);
        }

        if (widgetClassName == "QCheckBox") {
            auto checkBox = new QCheckBox;
            QString checkState = values[settingsID].toString();

            if (checkState.toInt() == 0)
                checkBox->setCheckState(Qt::CheckState::Unchecked);
            else
                checkBox->setCheckState(Qt::CheckState::Checked);

            connect(checkBox,static_cast<void (QCheckBox::*)(int state)>(&QCheckBox::stateChanged), this, [settingsID, extension, checkState]() {
                extension->updateSettings(settingsID, checkState == "0" ? "2" : "0");
            });

            // Add a new row
            tableAppsList->insertRow(tableAppsList->rowCount());
            tableAppsList->setCellWidget(tableAppsList->rowCount() - 1, 0, checkBox);
        }
    }*/

    // Set the settings widget in the scroll area
    ui->scrollArea_Apps->setWidget(tableAppsList);
}