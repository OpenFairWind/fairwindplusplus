
#include <FairWindSdk/FairWind.hpp>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <FairWindSdk/settings/FairLineEdit.hpp>
#include <FairWindSdk/IApp.hpp>

void fairwind::ui::settings::FairLineEdit::setDetails(QJsonObject settings, QJsonObject values, fairwind::apps::IApp* extension) {
    auto settingsID = settings["id"].toString();

    this->setText(values[settingsID].toString());

    connect(this,static_cast<void (QLineEdit::*)(const QString& newValue)>(&QLineEdit::textChanged), this, [settingsID, extension](QString newValue) {
        extension->updateSettings(settingsID, newValue);
    });
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::FairLineEdit::getNewInstance() {
    return static_cast<ISettings *>(new FairLineEdit());
}

QString fairwind::ui::settings::FairLineEdit::getClassName() {
    return this->metaObject()->className();
}
