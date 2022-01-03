//
// Created by Raffaele Montella on 03/01/22.
//

#include <util/ExtendedJsonSchema.hpp>

#include "FairWindSdk/util/ExtendedJsonSchema.hpp"

fairwind::ExtendedJsonSchema::ExtendedJsonSchema(QJsonObject schema) {



    m_schema = schema;
    if (!m_schema.contains(m_definitions)) {
        m_schema[m_definitions] = {};
    }

    QJsonObject objectSettingsDefs=m_schema[m_definitions].toObject();


    for(auto schema:m_schemas) {
        QFile schemaFile(schema);
        if (schemaFile.exists()) {
            schemaFile.open(QFile::ReadOnly);
            if (schemaFile.isOpen()) {
                auto displaySchemaDoc = QJsonDocument::fromJson(schemaFile.readAll());
                QJsonObject objectDisplaySchema = displaySchemaDoc.object();
                if (objectDisplaySchema.contains(m_definitions) && objectDisplaySchema[m_definitions].isObject()) {
                    QJsonObject objectDefs = objectDisplaySchema[m_definitions].toObject();
                    for (auto key: objectDefs.keys()) {
                        objectSettingsDefs[key] = objectDefs[key];
                    }
                }
                schemaFile.close();
            }
        }
    }
    m_schema[m_definitions] = objectSettingsDefs;

}

bool fairwind::ExtendedJsonSchema::validate(const QVariant &instance) {
    JsonSchema jsonSchema = JsonSchema::fromJson(m_schema);
    return jsonSchema.validate(instance);
}

bool fairwind::ExtendedJsonSchema::validate(const QByteArray &instance) {
    JsonSchema jsonSchema = JsonSchema::fromJson(m_schema);
    return jsonSchema.validate(instance);
}

bool fairwind::ExtendedJsonSchema::validate(const QJsonValue &instance) {
    JsonSchema jsonSchema = JsonSchema::fromJson(m_schema);
    return jsonSchema.validate(instance);
}

bool fairwind::ExtendedJsonSchema::validate(const QJsonDocument &instance) {
    JsonSchema jsonSchema = JsonSchema::fromJson(m_schema);
    return jsonSchema.validate(instance);
}

QJsonObject fairwind::ExtendedJsonSchema::toObject() {
    return m_schema;
}

QJsonDocument fairwind::ExtendedJsonSchema::toDocument() {
    QJsonDocument doc(m_schema);
    return doc;
}

JsonSchema fairwind::ExtendedJsonSchema::toJsonSchema() {
    return JsonSchema::fromJson(m_schema);
}

QJsonDocument fairwind::ExtendedJsonSchema::getDefaultConfig() {
    return QJsonDocument();
}


