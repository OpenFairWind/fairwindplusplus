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

/*
 * Creare a default config.json from the extended json schema
 *
 * ToDo: recursive implementation
 */
QJsonDocument fairwind::ExtendedJsonSchema::getDefaultConfig() {
    // Create the root
    QJsonObject root;

    // Check if the schema contains the required key
    if (m_schema.contains("required") && m_schema["required"].isArray()) {

        // Get the array of the required keys
        QJsonArray arrayRequired = m_schema["required"].toArray();

        // Check if the schema contains the properties key
        if (m_schema.contains("properties") && m_schema["properties"].isObject()) {

            // Get the properties object
            QJsonObject objectProperties = m_schema["properties"].toObject();

            // For each required key
            for (const auto item: arrayRequired) {

                // Check if the item is a string
                if (item.isString()) {

                    // Get the key string
                    QString key = item.toString();

                    // Check if the properties object contains the key
                    if (objectProperties.contains(key) && objectProperties[key].isObject()) {

                        // Get the property object
                        QJsonObject objectProperty = objectProperties[key].toObject();

                        // Check if the property contains the "defaultValue" key
                        if (objectProperty.contains("defaultValue")) {

                            // Check if the property contains the "type" key
                            if (objectProperty.contains("type") && objectProperty["type"].isString()) {

                                // Get the type key
                                QString type = objectProperty["type"].toString();

                                // Check if the type is a string
                                if (type == "string") {
                                    // Check if the default value matches with the json schema type
                                    if (objectProperty["defaultValue"].isString()) {
                                        // Create the key in the root and assign the value
                                        root[key] = objectProperty["defaultValue"].toString();
                                    }
                                    // Check if the type os a boolean
                                } else if (type == "boolean") {
                                    // Check if the default value matches with the json schema type
                                    if (objectProperty["defaultValue"].isBool()) {
                                        // Create the key in the root and assign the value
                                        root[key] = objectProperty["defaultValue"].toBool();
                                    }
                                    // Check if the type os a number
                                } else if (type == "number") {
                                    // Check if the default value matches with the json schema type
                                    if (objectProperty["defaultValue"].isDouble()) {
                                        // Create the key in the root and assign the value
                                        root[key] = objectProperty["defaultValue"].toDouble();
                                    }
                                    // Check if the type os a integer
                                } else if (type == "integer") {
                                    // Check if the default value matches with the json schema type
                                    if (objectProperty["defaultValue"].isDouble()) {
                                        // Create the key in the root and assign the value
                                        root[key] = (int) (objectProperty["defaultValue"].toDouble());
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Create the json document
    QJsonDocument jsonDocument;

    // Set the root
    jsonDocument.setObject(root);

    // Return the json document
    return jsonDocument;
}


