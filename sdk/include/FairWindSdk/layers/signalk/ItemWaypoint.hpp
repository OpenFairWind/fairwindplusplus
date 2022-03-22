//
// Created by Raffaele Montella on 14/03/22.
//

#ifndef FAIRWIND_ITEMWAYPOINT_HPP
#define FAIRWIND_ITEMWAYPOINT_HPP


#include <FairWindSDK.hpp>
#include "ItemSignalK.hpp"

namespace fairwind::layers::signalk {
    class FAIRWINDSDK_LIB_DECL ItemWaypoint : public ItemSignalK {
    Q_OBJECT
    public:
        explicit ItemWaypoint(QString &typeUuid);

        QImage getImage() const override;

    private:
    };
}

#endif //FAIRWIND_ITEMWAYPOINT_HPP
