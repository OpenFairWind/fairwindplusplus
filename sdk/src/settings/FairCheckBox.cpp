#include <QCheckBox>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/FairCheckBox.hpp>
#include <QGridLayout>
#include <QLabel>

void fairwind::ui::settings::FairCheckBox::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    auto layout = new QGridLayout;
    // Get the settings ID
    auto settingsID = settings["id"].toString();
    // Create a label
    auto label = new QLabel(settings["displayName"].toString() + ":");
    auto checkBox = new QCheckBox;

    QFont font = QFont("", 20);

    label->setFont(font);

    // Get the settings current value
    QString checkState = values[settingsID].toString();

    // Set the checkbox's state according to the current value
    if (checkState.toInt() == 0)
        checkBox->setCheckState(Qt::CheckState::Unchecked);
    else
        checkBox->setCheckState(Qt::CheckState::Checked);

    // When the current value changes, call the updateSettings method to save the changes
    connect(checkBox,static_cast<void (QCheckBox::*)(int state)>(&QCheckBox::stateChanged), this, [settingsID, extension, checkState]() {
        extension->updateSettings(settingsID, checkState == "0" ? "2" : "0");
    });

    layout->addWidget(label, 0, 0);
    layout->addWidget(checkBox, 0, 1);

    this->setLayout(layout);
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairCheckBox::getNewInstance() {
    return static_cast<ISettings *>(new FairCheckBox());
}

QString fairwind::ui::settings::FairCheckBox::getClassName() {
    return this->metaObject()->className();
}