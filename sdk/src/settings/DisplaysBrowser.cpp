#include <QHBoxLayout>
#include <QJsonObject>
#include <QCheckBox>
#include <QString>
#include <QJsonArray>
#include <QLabel>
#include <QDebug>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/IApp.hpp>
#include <FairWindSdk/settings/DisplaysBrowser.hpp>

void fairwind::ui::settings::DisplaysBrowser::setDetails(QString settingsID, QJsonObject settings, fairwind::apps::IApp* extension) {
    auto fairWind = fairwind::FairWind::getInstance();
    auto configs = extension->getConfig();
    auto displays = configs[settingsID].toArray();
    auto displaysLayout = new QVBoxLayout;

    for (int i = 0; i < displays.size(); i++) {
        auto display = fairWind->instanceDisplay(displays[i].toObject()["class"].toString());

        if (display != nullptr) {
            auto layout = new QHBoxLayout;
            auto widget = new QWidget;
            auto label = new QLabel;
            auto icon = new QLabel;
            auto checkBox = new QCheckBox;

            icon->setPixmap(QPixmap::fromImage(display->getIcon()));
            label->setText(displays[i].toObject()["class"].toString());
            label->setFont(QFont("", 14));
            label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

            auto checkState = displays[i].toObject()["active"].toBool();

            // Set the checkbox's state according to the current value
            if (checkState)
                checkBox->setCheckState(Qt::CheckState::Checked);
            else
                checkBox->setCheckState(Qt::CheckState::Unchecked);

            // When the current value changes, call the updateSettings method to save the changes
            connect(checkBox,static_cast<void (QCheckBox::*)(int state)>(&QCheckBox::stateChanged), this, [settingsID, extension, checkState]() {
                //extension->updateSettings(ref, checkState == "0" ? "2" : "0");
            });

            layout->addWidget(icon);
            layout->addWidget(label);
            layout->addWidget(checkBox);

            widget->setLayout(layout);

            displaysLayout->addWidget(widget);
        }
    }

    this->setLayout(displaysLayout);
}

fairwind::ui::settings::ISettings *fairwind::ui::settings::DisplaysBrowser::getNewInstance() {
    return static_cast<ISettings *>(new DisplaysBrowser());
}

QString fairwind::ui::settings::DisplaysBrowser::getClassName() {
    return this->metaObject()->className();
}