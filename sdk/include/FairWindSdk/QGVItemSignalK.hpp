//
// Created by Raffaele Montella on 03/05/21.
//

#ifndef FAIRWIND_QGVITEMSIGNALK_HPP
#define FAIRWIND_QGVITEMSIGNALK_HPP


#include <QGeoView/QGVImage.h>
#include <FairWindSDK.hpp>
#include <SignalKDocument.hpp>

class FAIRWINDSDK_LIB_DECL QGVItemSignalK: public QGVImage {
Q_OBJECT
public:
    explicit QGVItemSignalK(const QString &context);
    ~QGVItemSignalK();

    virtual QImage getImage() const = 0;

    QString getContext() const;

public slots:
    void update(const QJsonObject update);

private:
    QString m_context;
};


#endif //FAIRWIND_QGVITEMSIGNALK_HPP
