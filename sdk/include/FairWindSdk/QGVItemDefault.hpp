//
// Created by Raffaele Montella on 05/05/21.
//

#ifndef FAIRWIND_QGVITEMDEFAULT_HPP
#define FAIRWIND_QGVITEMDEFAULT_HPP

#include <FairWindSDK.hpp>
#include "QGVItemSignalK.hpp"

class FAIRWINDSDK_LIB_DECL QGVItemDefault: public QGVItemSignalK {
Q_OBJECT
public:
    explicit QGVItemDefault(QString &typeUuid);
    QImage getImage() const override;
private:
};

#endif //FAIRWIND_QGVITEMDEFAULT_HPP
