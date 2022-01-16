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
        void setDetails(std::function<void(QVariant newValue)> slot, QJsonObject details, QJsonValue currentValue) override;
        ISettings* getNewInstance() override;
        QString getClassName() override;
    signals:
        void changed(QVariant newValue) override;
    };
}

#endif //FAIRWIND_FAIRCHECKBOX_HPP
