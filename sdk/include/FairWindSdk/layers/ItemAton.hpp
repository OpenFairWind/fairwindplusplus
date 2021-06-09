//
// Created by Raffaele Montella on 03/05/21.
//

#ifndef FAIRWIND_ITEMATON_HPP
#define FAIRWIND_ITEMATON_HPP

#include <FairWindSDK.hpp>
#include "ItemSignalK.hpp"

class FAIRWINDSDK_LIB_DECL ItemAton: public ItemSignalK {
Q_OBJECT
public:
    explicit ItemAton(QString &typeUuid);
    QImage getImage() const override;
private:
};

#endif //FAIRWIND_ITEMATON_HPP
