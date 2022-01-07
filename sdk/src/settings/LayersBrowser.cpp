#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QCheckBox>
#include <QString>
#include <QJsonArray>
#include <QLabel>
#include <QDebug>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/LayersBrowser.hpp>

void fairwind::ui::settings::LayersBrowser::setDetails(QString settingsID, QJsonObject settings, fairwind::apps::IApp* extension) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto configs = extension->getConfig();
    auto layers = configs[settingsID].toArray();
    auto layersLayout = new QVBoxLayout;

    for (int i = 0; i < layers.size(); i++) {
        auto layer = fairWind->instanceLayer(layers[i].toObject()["class"].toString());

        if (layer != nullptr) {
            auto vLayout = new QVBoxLayout;
            auto hLayout = new QHBoxLayout;
            auto vWidget = new QWidget;
            auto hWidget = new QWidget;
            auto label = new QLabel;
            auto icon = new QLabel;
            auto description = new QLabel;
            auto checkBox = new QCheckBox;

            icon->setPixmap(QPixmap::fromImage(layer->getIcon()));
            label->setText(layers[i].toObject()["name"].toString());
            label->setFont(QFont("", 14));

            description->setText(layers[i].toObject()["description"].toString());

            vLayout->addWidget(label);
            vLayout->addWidget(description);

            vWidget->setLayout(vLayout);
            vWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            QString checkState = layers[i].toObject()["active"].toString();

            // Set the checkbox's state according to the current value
            if (checkState.toInt() == 0)
                checkBox->setCheckState(Qt::CheckState::Unchecked);
            else
                checkBox->setCheckState(Qt::CheckState::Checked);

            // When the current value changes, call the updateSettings method to save the changes
            connect(checkBox,static_cast<void (QCheckBox::*)(int state)>(&QCheckBox::stateChanged), this, [settingsID, extension, checkState]() {
                //extension->updateSettings(settingsID, checkState == "0" ? "2" : "0");
            });

            hLayout->addWidget(icon);
            hLayout->addWidget(vWidget);
            hLayout->addWidget(checkBox);

            hWidget->setLayout(hLayout);

            layersLayout->addWidget(hWidget);
        }
    }

    this->setLayout(layersLayout);
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::LayersBrowser::getNewInstance() {
    return static_cast<ISettings *>(new LayersBrowser());
}

QString fairwind::ui::settings::LayersBrowser::getClassName() {
    return this->metaObject()->className();
}