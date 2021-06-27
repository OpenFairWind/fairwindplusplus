//
// Created by Raffaele Montella on 08/04/21.
//

#ifndef FAIRWIND_APPBASE_HPP
#define FAIRWIND_APPBASE_HPP


#include <QJsonObject>
#include <FairWindSdk/FairWindSDK.hpp>

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL AppBase {
    public:
        ~AppBase() = default;

        virtual QString getId() const;
        virtual QString getName() const;
        virtual QString getDesc() const;

        virtual void onInit(QJsonObject *metaData);

        virtual QJsonObject getConfig();
        virtual QJsonObject getMetaData();

    private:
        QJsonObject m_metaData;
        QJsonObject m_config;
    };
}

#endif //FAIRWIND_APPBASE_HPP
