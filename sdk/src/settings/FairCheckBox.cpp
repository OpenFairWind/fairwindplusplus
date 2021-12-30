#include <QCheckBox>
#include <QString>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/FairCheckBox.hpp>

void fairwind::ui::settings::FairCheckBox::setDetails(QString settingsID, QJsonObject settings, fairwind::apps::IApp* extension) {
    auto config = extension->getConfig();

    // Get the settings current value
    QString checkState = config[settingsID].toString();

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