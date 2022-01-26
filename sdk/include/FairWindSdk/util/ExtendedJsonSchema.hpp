//
// Created by Raffaele Montella on 03/01/22.
//

#ifndef FAIRWIND_EXTENDEDJSONSCHEMA_HPP
#define FAIRWIND_EXTENDEDJSONSCHEMA_HPP

#include <QObject>
#include <QtJsonSchema/jsonschema.h>

#include <FairWindSdk/FairWindSDK.hpp>
#include <QJsonObject>

namespace fairwind {
    /*
     * ExtendedJsonSchema
     * This class provides a support in managing Json Schema in FairWind
     */
    class FAIRWINDSDK_LIB_DECL ExtendedJsonSchema : public QObject {
        Q_OBJECT


    public:
        ExtendedJsonSchema(QJsonObject schema, const QStringList& schemas);
        ExtendedJsonSchema(QJsonObject schema);


        bool validate(const QVariant &instance);
        bool validate(const QByteArray &instance);
        bool validate(const QJsonValue &instance);
        bool validate(const QJsonDocument &instance);

        QJsonObject toObject();
        QJsonDocument toDocument();
        JsonSchema toJsonSchema();

        QJsonDocument getDefaultConfig();

        QJsonValue getJsonValueByPath(QString path);

    private:
        QJsonObject m_schema;
        QString m_definitions="definitions";
        QStringList m_schemas = { ":/resources/schemas/display.json", ":/resources/schemas/layer.json"};
    };
}

#endif //FAIRWIND_EXTENDEDJSONSCHEMA_HPP
