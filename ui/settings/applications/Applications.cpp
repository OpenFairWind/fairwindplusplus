//
// Created by Raffaele Montella on 16/07/21.
//

#include <QTableWidgetItem>
#include <FairWindSdk/FairWind.hpp>

#include "Applications.hpp"
#include "ui_Applications.h"
#include "QJsonArray"
#include "QGroupBox"
#include "QPixmap"
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

    auto layout = ui->gridLayout_4;
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 2);

    // Get the table AppsList
    auto tableAppsList = ui->table_AppsList;
    this->setStyleSheet("background:#303030");

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
        // Get the reference to the application
        auto app = apps.values().at(current.row());

        // Store the extension id
        mExtension = app->getExtension();
    }

    // Get the extension reference by the application id
    auto extension = fairWind->getAppByExtensionId(mExtension);

    // Check if the extension is valid
    if (extension != nullptr) {
        // Get the extension's config
        auto configs = extension->getConfig();

        // Get the 'Settings' object from the config
        auto settings = configs["Settings"].toArray();
        // Get the 'Values' object from the config
        auto values = configs["Values"].toObject();

        // Prepare the settings container widget
        auto settingsContainer = new QWidget;
        auto layout = new QGridLayout;

        // Iterate on all the extension's settings
        for (int i = 0; i < settings.size(); i++) {
            // Generate the widget according to the provided class name
            auto widget = fairWind->instanceSettings(settings[i].toObject()["widgetClassName"].toString());
            // Create a label
            auto label = new QLabel(settings[i].toObject()["displayName"].toString() + ":");
            label->setFont(QFont("", 12));

            // Check if the widget is valid
            if (widget != nullptr) {
                // Set the details for the widget
                widget->setDetails(settings[i].toObject(), values, extension);

                // Add the label
                layout->addWidget(label, i, 0);
                // Add the widget to the container
                layout->addWidget(dynamic_cast<QWidget *>(widget), i, 1);
            }
        }

        auto displays = configs["Displays"].toArray();
        auto displaysList = new QGroupBox;
        displaysList->setTitle("Displays");
        auto displaysLayout = new QGridLayout;

        for (int i = 0; i < displays.size(); i++) {
            auto display = fairWind->instanceDisplay(displays[i].toObject()["class"].toString());

            if (display != nullptr) {
                auto label = new QLabel;

                label->setPixmap(QPixmap::fromImage(display->getIcon()));
                label->setText(displays[i].toObject()["class"].toString());
                label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

                displaysLayout->addWidget(label, i, 0);
            }
        }

        displaysList->setLayout(displaysLayout);

        layout->addWidget(displaysList, layout->rowCount(), 0);

        // Set the settings widget in the scroll area
        settingsContainer->setLayout(layout);
        ui->scrollArea_Apps->setWidget(settingsContainer);
    }
}