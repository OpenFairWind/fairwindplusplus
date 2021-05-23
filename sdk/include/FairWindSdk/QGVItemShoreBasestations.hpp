//
// Created by Raffaele Montella on 03/05/21.
//

#ifndef FAIRWIND_QGVITEMSHOREBASESTATIONS_HPP
#define FAIRWIND_QGVITEMSHOREBASESTATIONS_HPP

#include <FairWindSDK.hpp>
#include "QGVItemSignalK.hpp"

class FAIRWINDSDK_LIB_DECL QGVItemShoreBasestations: public QGVItemSignalK {
Q_OBJECT
public:
    explicit QGVItemShoreBasestations(QString &typeUuid);
    QImage getImage() const override;
private:
};


#endif //FAIRWIND_QGVITEMSHOREBASESTATIONS_HPP
