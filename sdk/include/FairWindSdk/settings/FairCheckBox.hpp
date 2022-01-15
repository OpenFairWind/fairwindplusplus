//
// Created by debian on 12/1/21.
//

#ifndef FAIRWIND_FAIRCHECKBOX_HPP
#define FAIRWIND_FAIRCHECKBOX_HPP

#include <FairWindSdk/ISettings.hpp>
#include <FairWindSdk/IFairWindApp.hpp>
#include <QCheckBox>

namespace fairwind::ui::settings {
    /*
     * FairCheckBox
     * This widget is a check box and presents a two-state box (checked/unchecked)
     */
    class FAIRWINDSDK_LIB_DECL FairCheckBox : public QCheckBox, public ISettings {
    Q_OBJECT

    public:
        void setDetails(QString settingsID, QJsonObject settings, fairwind::apps::IFairWindApp* extension) override;
        ISettings* getNewInstance() override;
        QString getClassName() override;
    };
}

#endif //FAIRWIND_FAIRCHECKBOX_HPP
