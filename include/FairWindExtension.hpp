//
// Created by Raffaele Montella on 08/04/21.
//

#ifndef FAIRWIND_FAIRWINDEXTENSION_HPP
#define FAIRWIND_FAIRWINDEXTENSION_HPP


#include <QJsonObject>

namespace fairwind::extensions {
    class FairWindExtension {
    public:
        ~FairWindExtension() = default;

        virtual QString getId() const;
        virtual QString getName() const;
        virtual QString getDesc() const;
        virtual void init(QJsonObject *metaData);

    private:
        QJsonObject m_metaData;
    };
}

#endif //FAIRWIND_FAIRWINDEXTENSION_HPP
