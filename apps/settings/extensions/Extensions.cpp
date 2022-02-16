//
// Created by Raffaele Montella on 23/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Extensions.h" resolved

#include <FairWindSdk/FairWind.hpp>
#include "Extensions.hpp"
#include "ui_Extensions.h"
#include "ExtensionItem.hpp"


namespace fairwind::apps::settings::extensions {
    Extensions::Extensions(QWidget *parent) :
            QWidget(parent), ui(new Ui::Extensions) {
        ui->setupUi(this);

        mBrowser = new browser::Browser(ui->scrollArea_Extension);
        ui->scrollArea_Extension->setLayout(new QVBoxLayout());
        ui->scrollArea_Extension->layout()->addWidget(mBrowser);

        // Update the UI when the current changes
        connect(ui->list_Extensions, &QListWidget::currentRowChanged, this, &Extensions::onCurrentRowChanged);

    }

    Extensions::~Extensions() {
        delete ui;
    }

    QString Extensions::getName() const {
        return tr("Extensions");
    }

    QString Extensions::getClassName() const {
        return this->metaObject()->className();
    }

    QImage Extensions::getIcon() const {
        return QImage(":resources/images/icons/extensions_icon.png");
    }

    ui::settings::ISettingsTab *Extensions::getNewInstance() {
        return static_cast<ISettingsTab *>(new Extensions());
    }

    void Extensions::showEvent(QShowEvent *event) {

        ui->list_Extensions->clear();

        auto fairwind = FairWind::getInstance();

        if (mExtensionId.isEmpty()) {
            mExtensionId = fairwind->getLauncherFairWindAppId();
        }

        for (const auto& extensionId:fairwind->getExtensionsIds()) {
            qDebug() << "Extensions::showEvent: extensionId:" << extensionId;
            auto fairWindApp = fairwind->getAppByExtensionId(extensionId);

            if (fairWindApp) {
                qDebug() << "Extensions::showEvent: " << fairWindApp->getId() << " :: " << fairWindApp->getName();
                auto widget = new ExtensionItem(ui->list_Extensions, fairWindApp);
                widget->setMinimumWidth(100);

                auto listWidgetItem = new QListWidgetItem();
                listWidgetItem->setSizeHint(widget->sizeHint());

                if (mExtensionId == extensionId) {
                    // qDebug() << "Extensions::showEvent mExtensionId == extensionId " << extensionId;

                    listWidgetItem->setSelected(true);
                    QJsonObject config = fairWindApp->getConfig();
                    mBrowser->setJsonObjectRoot(fairWindApp->getSettings(), config);
                }

                ui->list_Extensions->addItem(listWidgetItem);
                ui->list_Extensions->setItemWidget(listWidgetItem, widget);

                mMapListWidgetItem2ExtensionId[listWidgetItem] = extensionId;

            }
        }
        QWidget::showEvent(event);
    }

    void Extensions::onCurrentRowChanged(int currentRow) {

        // qDebug() << "Extensions::onCurrentRowChanged " << currentRow;

        auto fairwind = FairWind::getInstance();

        if (!mExtensionId.isEmpty()) {
            auto fairWindApp = fairwind->getAppByExtensionId(mExtensionId);
            if (fairWindApp){
                QJsonObject config = mBrowser->getJsonObjectRoot();
                fairWindApp->setConfig(config);
            }
        }

        auto selectedItem = ui->list_Extensions->currentItem();
        if (selectedItem){
            mExtensionId = mMapListWidgetItem2ExtensionId[selectedItem];
            qDebug() << "Selected mExtensionId:" << mExtensionId;
            qDebug() << "SelectedItem: " << selectedItem;
            selectedItem->setSelected(true);
        }
        else{
            qDebug() << "Not selected" << mExtensionId;
            selectedItem = mMapListWidgetItem2ExtensionId.key(mExtensionId);
            qDebug() << "SelectedItem: " << selectedItem;
            // selectedItem->setSelected(true);
        }

        auto fairWindApp = fairwind->getAppByExtensionId(mExtensionId);
        QJsonObject config = fairWindApp->getConfig();
        mBrowser->setJsonObjectRoot(fairWindApp->getSettings(), config);

    }


} // fairwind::apps::settings::extensions
