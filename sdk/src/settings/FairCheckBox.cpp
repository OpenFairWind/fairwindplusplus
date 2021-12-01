
#include <FairWindSdk/FairWind.hpp>
#include <QCheckBox>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <FairWindSdk/settings/FairCheckBox.hpp>
#include <FairWindSdk/IApp.hpp>

void fairwind::ui::settings::FairCheckBox::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    auto settingsID = settings["id"].toString();

    QString checkState = values[settingsID].toString();

    if (checkState.toInt() == 0)
        this->setCheckState(Qt::CheckState::Unchecked);
    else
        this->setCheckState(Qt::CheckState::Checked);

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
