//
// Created by Raffaele Montella on 14/03/22.
//

#ifndef FAIRWIND_ITEMNOTE_HPP
#define FAIRWIND_ITEMNOTE_HPP


#include <FairWindSdk/FairWindSDK.hpp>
#include "ItemSignalK.hpp"

namespace fairwind::layers::signalk {
    class FAIRWINDSDK_LIB_DECL ItemNote : public ItemSignalK {
    Q_OBJECT
    public:
        explicit ItemNote(QString &typeUuid);

        QImage getImage() const override;

    private:
    };
}

#endif //FAIRWIND_ITEMNOTE_HPP
