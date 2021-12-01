
#include <FairWindSdk/FairWind.hpp>
#include <QCheckBox>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <FairWindSdk/settings/FairCheckBox.hpp>
#include <FairWindSdk/IApp.hpp>

void fairwind::ui::settings::FairCheckBox::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    // Get the settings ID
    auto settingsID = settings["id"].toString();

    // Get the settings current value
    QString checkState = values[settingsID].toString();

    // Set the checkbox's state according to the current value
    if (checkState.toInt() == 0)
        this->setCheckState(Qt::CheckState::Unchecked);
    else
        this->setCheckState(Qt::CheckState::Checked);

    // When the current value changes, call the updateSettings method to save the changes
    connect(this,static_cast<void (QCheckBox::*)(int state)>(&QCheckBox::stateChanged), this, [settingsID, extension, checkState]() {
        extension->updateSettings(settingsID, checkState == "0" ? "2" : "0");
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairCheckBox::getNewInstance() {
    return static_cast<ISettings *>(new FairCheckBox());
}

QString fairwind::ui::settings::FairCheckBox::getClassName() {
    return this->metaObject()->className();
}
