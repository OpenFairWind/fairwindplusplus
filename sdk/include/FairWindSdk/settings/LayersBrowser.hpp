//
// Created by debian on 1/6/22.
//

#ifndef FAIRWIND_LAYERSBROWSER_HPP
#define FAIRWIND_LAYERSBROWSER_HPP

#include <FairWindSdk/ISettings.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <QGroupBox>
#include <QString>

namespace fairwind::ui::settings {
    /*
     * FairComboBox
     * This widget is a combo box and presents a dropwdown list of options
     */
    class FAIRWINDSDK_LIB_DECL LayersBrowser : public QGroupBox, public ISettings {
    Q_OBJECT

    public:
    void setDetails(QString settingID, QJsonObject settings, fairwind::apps::IFairWindApp* extension) override;
    ISettings* getNewInstance() override;
    QString getClassName() override;
};
}

#endif //FAIRWIND_LAYERSBROWSER_HPP
