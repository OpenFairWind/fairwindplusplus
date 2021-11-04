//
// Created by Raffaele Montella on 03/05/21.
//

#ifndef FAIRWIND_ITEMVESSEL_HPP
#define FAIRWIND_ITEMVESSEL_HPP

#include <FairWindSDK.hpp>

#include "ItemSignalK.hpp"

/*
 * ItemVessel
 * Layer item representing the vessel on the map
 */
class FAIRWINDSDK_LIB_DECL ItemVessel: public ItemSignalK {
Q_OBJECT
public:
    explicit ItemVessel(QString &typeUuid);
    QImage getImage() const override;
};

#endif //FAIRWIND_ITEMVESSEL_HPP