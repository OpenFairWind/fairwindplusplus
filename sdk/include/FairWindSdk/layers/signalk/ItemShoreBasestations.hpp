//
// Created by Raffaele Montella on 03/05/21.
//

#ifndef FAIRWIND_ITEMSHOREBASESTATIONS_HPP
#define FAIRWIND_ITEMSHOREBASESTATIONS_HPP

#include <FairWindSDK.hpp>
#include "ItemSignalK.hpp"

namespace fairwind::layers::signalk {
    class FAIRWINDSDK_LIB_DECL ItemShoreBasestations : public ItemSignalK {
    Q_OBJECT
    public:
        explicit ItemShoreBasestations(QString &typeUuid);

        QImage getImage() const override;

    private:
    };
}

#endif //FAIRWIND_ITEMSHOREBASESTATIONS_HPP
