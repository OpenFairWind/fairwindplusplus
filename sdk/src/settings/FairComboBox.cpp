#include <QComboBox>
#include <QJsonObject>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/FairComboBox.hpp>
#include <QGridLayout>
#include <QLabel>

void fairwind::ui::settings::FairComboBox::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    auto layout = new QGridLayout;
    // Get the settings ID
    auto settingsID = settings["id"].toString();
    // Create a label
    auto label = new QLabel(settings["displayName"].toString() + ":");
    auto comboBox = new QComboBox;

    // Get the settings possible values
    auto domain = settings["domain"].toArray();

    label->setFont(QFont("", 12));
    comboBox->setFont(QFont("", 14));
    comboBox->setStyleSheet("background:#404040");

    // Add the current value
    comboBox->addItem(values[settingsID].toString());

    // Add the remaining values from the domain
    for (auto && j : domain) {
        if (j.toString() != values[settingsID].toString())
            comboBox->addItem(j.toString());
    }

    // When the current value changes, call the updateSettings method to save the changes
    connect(comboBox,static_cast<void (QComboBox::*)(int index)>(&QComboBox::currentIndexChanged), this, [settingsID, extension, comboBox]() {
        extension->updateSettings(settingsID, comboBox->currentText());
    });

    layout->addWidget(label, 0, 0);
    layout->addWidget(comboBox, 0, 1);

    layout->setColumnStretch(0, 2);
    layout->setColumnStretch(1, 8);

    this->setLayout(layout);
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairComboBox::getNewInstance() {
    return static_cast<ISettings *>(new FairComboBox());
}

QString fairwind::ui::settings::FairComboBox::getClassName() {
    return this->metaObject()->className();
}