//
// Created by Raffaele Montella on 05/05/21.
//

#ifndef FAIRWIND_ITEMDEFAULT_HPP
#define FAIRWIND_ITEMDEFAULT_HPP

#include <FairWindSDK.hpp>
#include "ItemSignalK.hpp"

/*
 * ItemDefault
 * Basic item widget for FairWind
 */
class FAIRWINDSDK_LIB_DECL ItemDefault: public ItemSignalK {
Q_OBJECT
public:
    explicit ItemDefault(QString &typeUuid);
    QImage getImage() const override;
private:
};

#endif //FAIRWIND_ITEMDEFAULT_HPP