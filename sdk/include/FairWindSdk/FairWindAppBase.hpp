//
// Created by Raffaele Montella on 08/04/21.
//

#ifndef FAIRWIND_FAIRWINDAPPBASE_HPP
#define FAIRWIND_FAIRWINDAPPBASE_HPP


#include <QJsonObject>
#include <FairWindSdk/FairWindSDK.hpp>

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL FairWindAppBase {
    public:
        ~FairWindAppBase() = default;

        virtual QString getId() const;
        virtual QString getName() const;
        virtual QString getDesc() const;
        virtual void onInit(QJsonObject *metaData);

        virtual QJsonObject getConfig();

    private:
        QJsonObject m_metaData;
    };
}

#endif //FAIRWIND_FAIRWINDAPPBASE_HPP
