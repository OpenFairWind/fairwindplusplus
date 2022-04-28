//
// Created by Raffaele Montella on 03/05/21.
//

#ifndef FAIRWIND_ITEMSIGNALK_HPP
#define FAIRWIND_ITEMSIGNALK_HPP

#include <QGeoView/QGVImage.h>

#include <FairWindSDK.hpp>
#include <FairWindSdk/signalk/Document.hpp>

namespace fairwind::layers::signalk {
    class FAIRWINDSDK_LIB_DECL ItemSignalK : public QGVImage {
    Q_OBJECT
    public:
        explicit ItemSignalK(const QString &context);

        ~ItemSignalK();

        virtual QImage getImage() const = 0;

        QString getContext() const;

    public slots:

        void update(const QJsonObject& update);

    private:
        QString m_context;
    };
}
#endif //FAIRWIND_ITEMSIGNALK_HPP
