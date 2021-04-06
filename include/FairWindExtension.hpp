//
// Created by Raffaele Montella on 03/04/21.
//

#ifndef FAIRWIND_FAIRWINDEXTENSION_HPP
#define FAIRWIND_FAIRWINDEXTENSION_HPP


#include <QJsonObject>
#include <QJsonDocument>

namespace fairwind::extensions {
    class FairWindExtension {
    public:
        virtual QString getId() const;
        virtual QString getName() const;
        virtual QString getDesc() const;
        virtual void setMetaData(QJsonObject &metaData);

    private:
        QJsonObject m_metaData;
    };
}


#endif //FAIRWIND_FAIRWINDEXTENSION_HPP
