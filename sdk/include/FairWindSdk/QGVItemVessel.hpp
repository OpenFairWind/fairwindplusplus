//
// Created by Raffaele Montella on 03/05/21.
//

#ifndef FAIRWIND_QGVITEMVESSEL_HPP
#define FAIRWIND_QGVITEMVESSEL_HPP

#include <FairWindSDK.hpp>
#include "QGVItemSignalK.hpp"

class FAIRWINDSDK_LIB_DECL QGVItemVessel: public QGVItemSignalK {
Q_OBJECT
public:
    explicit QGVItemVessel(QString &typeUuid);
    QImage getImage() const override;


};


#endif //FAIRWIND_QGVITEMVESSEL_HPP
