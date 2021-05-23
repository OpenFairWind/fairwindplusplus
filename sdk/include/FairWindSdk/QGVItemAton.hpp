//
// Created by Raffaele Montella on 03/05/21.
//

#ifndef FAIRWIND_QGVITEMATON_HPP
#define FAIRWIND_QGVITEMATON_HPP

#include <FairWindSDK.hpp>
#include "QGVItemSignalK.hpp"

class FAIRWINDSDK_LIB_DECL QGVItemAton: public QGVItemSignalK {
Q_OBJECT
public:
    explicit QGVItemAton(QString &typeUuid);
    QImage getImage() const override;
private:
};

#endif //FAIRWIND_QGVITEMATON_HPP
