//
// Created by Raffaele Montella on 14/03/22.
//

#ifndef FAIRWIND_ITEMREGION_HPP
#define FAIRWIND_ITEMREGION_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include "ItemSignalK.hpp"

namespace fairwind::layers::signalk {
    class FAIRWINDSDK_LIB_DECL ItemRegion : public ItemSignalK {
    Q_OBJECT
    public:
        explicit ItemRegion(QString &typeUuid);

        QImage getImage() const override;

    private:
    };
}

#endif //FAIRWIND_ITEMREGION_HPP
