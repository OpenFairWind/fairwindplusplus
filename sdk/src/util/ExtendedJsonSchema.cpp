//
// Created by Raffaele Montella on 03/01/22.
//

#include <util/ExtendedJsonSchema.hpp>

#include "FairWindSdk/util/ExtendedJsonSchema.hpp"
#include <utility>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>


/*
 * Construct an ExtendedJsonSchema object
 * schema: the root of the extended json schema (for example the application's settings in m_settings attribute
 * schemas: an array of strings with other json files containing definitions
 */
fairwind::ExtendedJsonSchema::ExtendedJsonSchema(QJsonObject schema, const QStringList& schemas) {

    // Set the schema as base extended json schema
    m_schema = std::move(schema);

    // Check if the schema doesn't contain the definitions
    if (!m_schema.contains(m_definitions)) {

        // Add the definitions key as an empty object
        m_schema[m_definitions] = {};
    }

    // For each item contained in the schemas parameter...
    for(const auto& item:schemas) {
        // Add the item to the m_schemas
        m_schemas.append(item);
    }

    // Get the definitions' object
    QJsonObject objectSettingsDefs=m_schema[m_definitions].toObject();

    // For each item in the schemas...
    for(const auto& item:m_schemas) {

        // Set the file resource where the schema is stored
        QFile schemaFile(item);

        // Check if the file resource exists
        if (schemaFile.exists()) {

            // Open the file resource in read only mode
            schemaFile.open(QFile::ReadOnly);

            // Check if the file is actually opended
            if (schemaFile.isOpen()) {

                // Read the whole file content and create a json document
                auto displaySchemaDoc = QJsonDocument::fromJson(schemaFile.readAll());

                // Get the json document root
                QJsonObject objectDisplaySchema = displaySchemaDoc.object();

                // Check if the root contains the definition key and the value is actually an object
                if (objectDisplaySchema.contains(m_definitions) && objectDisplaySchema[m_definitions].isObject()) {

                    // Get the definitions object
                    QJsonObject objectDefs = objectDisplaySchema[m_definitions].toObject();

                    // For each key in the definition object...
                    for (const auto& key: objectDefs.keys()) {

                        // Add the key to the extended json schema
                        objectSettingsDefs[key] = objectDefs[key];
                    }
                }

                // Close the file
                schemaFile.close();
            }
        }
    }

    // Add the definitions to the extended json schema
    m_schema[m_definitions] = objectSettingsDefs;
}

/*
 * Construct an ExtendedJsonSchema object
 * schema: the root of the extended json schema (for example the application's settings in m_settings attribute
 * Use this constructor if no other json files are needed.
 */
fairwind::ExtendedJsonSchema::ExtendedJsonSchema( QJsonObject schema): ExtendedJsonSchema(std::move(schema), QStringList()) {}

/*
 * Validate a json file stored in a QVariant instance
 * instance: the json file
 */
bool fairwind::ExtendedJsonSchema::validate(const QVariant &instance) {
    // Create a JsonSchema object
    auto jsonSchema = JsonSchema::fromJson(m_schema);

    // Validate the instace versus the json schema
    return jsonSchema.validate(instance);
}

/*
 * Validate a json file stored in a QByteArray instance
 * instance: the json file
 */
bool fairwind::ExtendedJsonSchema::validate(const QByteArray &instance) {
    // Create a JsonSchema object
    auto jsonSchema = JsonSchema::fromJson(m_schema);

    // Validate the instace versus the json schema
    return jsonSchema.validate(instance);
}

/*
 * Validate a json file stored in a QJsonValue instance
 * instance: the json file
 */
bool fairwind::ExtendedJsonSchema::validate(const QJsonValue &instance) {
    // Create a JsonSchema object
    auto jsonSchema = JsonSchema::fromJson(m_schema);

    // Validate the instace versus the json schema
    return jsonSchema.validate(instance);
}

/*
 * Validate a json file stored in a QJsonDocument instance
 * instance: the json file
 */
bool fairwind::ExtendedJsonSchema::validate(const QJsonDocument &instance) {
    // Create a JsonSchema object
    auto jsonSchema = JsonSchema::fromJson(m_schema);

    // Validate the instace versus the json schema
    return jsonSchema.validate(instance);
}

/*
 * Returns the resulting schema as a QJsonObject
 */
QJsonObject fairwind::ExtendedJsonSchema::toObject() {
    // Return the extended json schema
    return m_schema;
}

/*
 * Returns the resulting schema as a QJsonDocument
 */
QJsonDocument fairwind::ExtendedJsonSchema::toDocument() {
    // Create a QJsonDocument from the extended json schema
    QJsonDocument jsonDocument(m_schema);

    // Return the json document
    return jsonDocument;
}

/*
 * Returns the resulting schema as a JsonSchema instance
 */
JsonSchema fairwind::ExtendedJsonSchema::toJsonSchema() {

    // Create a JsonSchema from the extend json schema and returns it to the caller
    return JsonSchema::fromJson(m_schema);
}

void fairwind::ExtendedJsonSchema::fillDefaultConfig(QJsonObject *jsonObjectRoot, QJsonObject schema) {

    qDebug() << "fairwind::ExtendedJsonSchema::fillDefaultConfig";
    qDebug() << jsonObjectRoot;
    qDebug() << "--------------------";
    qDebug() << schema;

    // Check if schema is an object
    if (schema.contains("type") && schema["type"].isString() && schema["type"].toString() == "object") {

        // Check if the schema contains the required key
        if (schema.contains("required") && schema["required"].isArray()) {

            // Get the array of the required keys
            QJsonArray arrayRequired = schema["required"].toArray();

            // Check if the schema contains the properties key
            if (schema.contains("properties") && schema["properties"].isObject()) {

                // Get the properties object
                QJsonObject objectProperties = schema["properties"].toObject();

                // For each required key
                for (const auto item: arrayRequired) {

                    // Check if the item is a string
                    if (item.isString()) {

                        // Get the key string
                        QString key = item.toString();
                        qDebug() << "KEY: "<< key;

                        // Check if the properties object contains the key
                        if (objectProperties.contains(key) && objectProperties[key].isObject()) {

                            // Get the property object
                            QJsonObject objectProperty = objectProperties[key].toObject();


                            // Check if the property contains the "type" key
                            if (objectProperty.contains("type") && objectProperty["type"].isString()) {

                                // Get the type key
                                QString type = objectProperty["type"].toString();

                                // Check if the property contains the "default" key
                                if (objectProperty.contains("default")){
                                    if (type == "string" || type == "boolean" || type == "number" || type == "integer") {
                                        // Check if the type is a string
                                        if (type == "string") {
                                            // Check if the default value matches with the json schema type
                                            if (objectProperty["default"].isString()) {
                                                // Create the key in the root and assign the value
                                                jsonObjectRoot->operator[](key) = objectProperty["default"].toString();
                                            }
                                            // Check if the type os a boolean
                                        } else if (type == "boolean") {
                                            // Check if the default value matches with the json schema type
                                            if (objectProperty["default"].isBool()) {
                                                // Create the key in the root and assign the value
                                                jsonObjectRoot->operator[](key) = objectProperty["default"].toBool();
                                            }
                                            // Check if the type os a number
                                        } else if (type == "number") {
                                            // Check if the default value matches with the json schema type
                                            if (objectProperty["default"].isDouble()) {
                                                // Create the key in the root and assign the value
                                                jsonObjectRoot->operator[](key) = objectProperty["default"].toDouble();
                                            }
                                            // Check if the type os a integer
                                        } else if (type == "integer") {
                                            // Check if the default value matches with the json schema type
                                            if (objectProperty["default"].isDouble()) {
                                                // Create the key in the root and assign the value
                                                jsonObjectRoot->operator[](
                                                        key) = (int) (objectProperty["default"].toDouble());
                                            }
                                        }
                                    }
                                    else if (type == "object") {
                                        QJsonObject jsonObject;
                                        fillDefaultConfig(&jsonObject, objectProperty);
                                        jsonObjectRoot->operator[](key) = jsonObject;
                                    }
                                } else{
                                    if (type == "string" || type == "boolean" || type == "number" || type == "integer") {
                                        // Check if the type is a string
                                        if (type == "string") {
                                            // Create the key in the root and assign the value
                                            jsonObjectRoot->operator[](key) = "";

                                            // Check if the type os a boolean
                                        } else if (type == "boolean") {
                                            // Create the key in the root and assign the value
                                            jsonObjectRoot->operator[](key) = false;

                                            // Check if the type os a number
                                        } else if (type == "number") {
                                            // Create the key in the root and assign the value
                                            jsonObjectRoot->operator[](key) = 0.0;
                                            // Check if the type os a integer
                                        } else if (type == "integer") {
                                            // Create the key in the root and assign the value
                                            jsonObjectRoot->operator[](key) = (int) 0;
                                        }
                                    }
                                    else if (type == "object") {
                                        // TODO Check this
                                        QJsonObject jsonObject;
                                        fillDefaultConfig(&jsonObject, objectProperty);
                                        jsonObjectRoot->operator[](key) = jsonObject;
                                    }
                                }

                            }
                        }
                    }
                }
            }
        }
    }
}

/*
 * Create a default config.json from the extended json schema
 *
 * ToDo: array implementation
 */
QJsonDocument fairwind::ExtendedJsonSchema::getDefaultConfig() {
    // Create the root
    QJsonObject root;

    fillDefaultConfig(&root, m_schema);

    // Create the json document
    QJsonDocument jsonDocument;

    // Set the root
    jsonDocument.setObject(root);

    qDebug() << "fairwind::ExtendedJsonSchema::getDefaultConfig jsonDocument " << jsonDocument.object();

    // Return the json document
    return jsonDocument;
}

QJsonValue fairwind::ExtendedJsonSchema::getJsonValueByPath(QString path) {
    // qDebug() << "fairwind::ExtendedJsonSchema::getJsonValueByPath: " << path;

    auto pathItems = path.split(":");
    int idx = 0;
    auto schema = m_schema;
    while (idx < pathItems.size()){
        if (schema.contains("properties") && schema["properties"].isObject()){
            auto jsonObjectProperties = schema["properties"].toObject();

            if (jsonObjectProperties.contains(pathItems[idx]) && jsonObjectProperties[pathItems[idx]].isObject()){
                auto jsonObjectProperty = jsonObjectProperties[pathItems[idx]].toObject();
                if (idx == pathItems.size() - 1) {
                    return jsonObjectProperty;
                } else {
                    schema = jsonObjectProperty;
                }
            }
        } else if (schema.contains("items") && schema["items"].isArray() && QRegExp("[0-9]*").exactMatch(pathItems[idx])){
            auto jsonObjectItem = schema["items"].toArray()[0];

            if (idx == pathItems.size() - 1) {
                return jsonObjectItem;
            } else {
                schema = jsonObjectItem.toObject();
            }
        }
        idx++;
    }

    return QJsonValue();
}



