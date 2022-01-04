//
// Created by Raffaele Montella on 03/01/22.
//

#ifndef FAIRWIND_EXTENDEDJSONSCHEMA_HPP
#define FAIRWIND_EXTENDEDJSONSCHEMA_HPP

#include <QtJsonSchema/jsonschema.h>

namespace fairwind {
    /*
     * ExtendedJsonSchema
     * This class provides a support in managing Json Schema in FairWind
     */
    class ExtendedJsonSchema {
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

    private:
        QJsonObject m_schema;
        QString m_definitions="definitions";
        QStringList m_schemas = { ":/resources/schemas/display.json", ":/resources/schemas/layer.json"};
    };
}

#endif //FAIRWIND_EXTENDEDJSONSCHEMA_HPP
