//
// Created by Raffaele Montella on 08/04/21.
//

#ifndef FAIRWIND_FAIRWINDAPPBASE_HPP
#define FAIRWIND_FAIRWINDAPPBASE_HPP


#include <QJsonObject>

namespace fairwind {
    class FairWindAppBase {
    public:
        ~FairWindAppBase() = default;

        virtual QString getId() const;
        virtual QString getName() const;
        virtual QString getDesc() const;
        virtual void init(QJsonObject *metaData);

    private:
        QJsonObject m_metaData;
    };
}

#endif //FAIRWIND_FAIRWINDAPPBASE_HPP
