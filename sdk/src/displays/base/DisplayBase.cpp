//
// Created by Raffaele Montella on 05/06/21.
//

#include <QJsonValue>
#include <QJsonArray>

#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/util/Units.hpp>

#include "FairWindSdk/displays/DisplayBase.hpp"

namespace fairwind::displays {
/*
 * DisplayBase - Public Constructor
 */
    DisplayBase::DisplayBase() {
        mFormat = QChar('f');
        mFillChar = QChar('0');
        mPrecision = 1;
        mFieldWidth = 3;
        mDstUnits = "";
    }

/*
 * ~DisplayBase - Destructor
 */
    DisplayBase::~DisplayBase() {}

/*
 * subscribe
 * Subscribe the new display to the SignalK document, in order to update its details when needed
 */
    void DisplayBase::subscribe(QString fullPath) {
        // Get the FairWind singleton
        auto fairWind = fairwind::FairWind::getInstance();
        // Get the SignalK document
        auto signalKDocument = fairWind->getSignalKDocument();

        // Update the full path with the new self key
        mFullPath = fullPath.replace("${self}", signalKDocument->getSelf());
        qDebug() << "DisplayBase::subscribe: " << mFullPath;

        // Get the information from the SignalK document
        QJsonValue jsonValue = signalKDocument->subtree(mFullPath);
        // Check if the information are valid
        if (jsonValue.isObject()) {
            QJsonObject jsonObject = jsonValue.toObject();
            // Check if the information contain a meta key
            if (jsonObject.contains("meta") && jsonObject["meta"].isObject()) {
                // Load metadata: units and description
                QJsonObject objectMeta = jsonObject["meta"].toObject();
                if (objectMeta.contains("units") && objectMeta["units"].isString()) {
                    mSrcUnits = objectMeta["units"].toString();
                }
                if (objectMeta.contains("description") && objectMeta["description"].isString()) {
                    mDescription = objectMeta["description"].toString();
                }
            }
            auto parts = mFullPath.split(".");
            parts.removeFirst();
            parts.removeFirst();
            auto key = parts.join(".");

            qDebug() << "DisplaySingleText::subscribe: key" << key;
            // Get the configuration from the FairWind singleton itself
            auto config = fairWind->getConfig();
            // Check if a SignalK configuration is present
            if (config.contains("SignalK") && config["SignalK"].isObject()) {
                // Load the SignalK document keys and their details
                QJsonObject objectSignalK = config["SignalK"].toObject();
                if (objectSignalK.contains("keys") && objectSignalK["keys"].isObject()) {
                    QJsonObject objectKeys = objectSignalK["keys"].toObject();
                    if (objectKeys.contains(key) && objectKeys[key].isObject()) {
                        QJsonObject objectKey = objectKeys[key].toObject();
                        if (objectKey.contains("label") && objectKey["label"].isString()) {
                            setLabel(objectKey["label"].toString());
                        }
                        if (objectKey.contains("format") && objectKey["format"].isString()) {
                            mFormat = objectKey["format"].toString().at(0);
                        }
                        if (objectKey.contains("precision") && objectKey["precision"].isDouble()) {
                            mPrecision = objectKey["precision"].toDouble();
                        }
                        if (objectKey.contains("fieldWidth") && objectKey["fieldWidth"].isDouble()) {
                            mFieldWidth = objectKey["fieldWidth"].toDouble();
                            QString text = "";
                            for (int i = 0; i < mFieldWidth; i++) {
                                text = text + "0";
                            }
                            setValue(text);
                        }
                        if (objectKey.contains("fillChar") && objectKey["fillChar"].isString()) {
                            mFillChar = objectKey["fillChar"].toString().at(0);
                        }
                        if (objectKey.contains("units") && objectKey["units"].isString()) {
                            mDstUnits = objectKey["units"].toString();
                            setUnits(fairwind::Units::getInstance()->getLabel(mDstUnits));
                        }
                    }
                }
            }

            if (jsonObject.contains("value") && jsonObject["value"].isDouble()) {
                QString text = "__.__";
                if (jsonObject["value"].isDouble()) {
                    double value = fairwind::Units::getInstance()->convert(
                            mSrcUnits, mDstUnits,
                            jsonObject["value"].toDouble());

                    text = QString{"%1"}.arg(value,
                                             mFieldWidth,
                                             mFormat.toLatin1(),
                                             mPrecision,
                                             mFillChar);

                } else if (jsonObject["value"].isString()) {
                    text = jsonObject["value"].toString();
                }
                setValue(text);
            }
        }
    }

    void DisplayBase::update(const QJsonObject update) {
        if (update.contains("updates") && update["updates"].isArray()) {
            QJsonArray arrayUpdates = update["updates"].toArray();
            if (arrayUpdates.size() == 1) {
                QJsonValue arrayUpdatesItem = arrayUpdates[0];
                if (arrayUpdatesItem.isObject()) {
                    QJsonObject arrayUpdatesItemObject = arrayUpdatesItem.toObject();
                    if (arrayUpdatesItemObject.contains("values") && arrayUpdatesItemObject["values"].isArray()) {
                        QJsonArray arrayValues = arrayUpdatesItemObject["values"].toArray();
                        for (auto arrayValuesItem: arrayValues) {
                            if (arrayValuesItem.isObject()) {
                                QJsonObject arrayValuesItemObject = arrayValuesItem.toObject();
                                if (arrayValuesItemObject.contains("path") &&
                                    arrayValuesItemObject["path"].isString()) {
                                    QString path = arrayValuesItemObject["path"].toString();

                                    if (mFullPath.endsWith(path)) {
                                        //qDebug() << "DisplaySingleText::path:" << path;
                                        if (arrayValuesItemObject.contains("value")) {

                                            QString text = "__.__";
                                            if (arrayValuesItemObject["value"].isDouble()) {
                                                double value = fairwind::Units::getInstance()->convert(
                                                        mSrcUnits, mDstUnits,
                                                        arrayValuesItemObject["value"].toDouble());

                                                text = QString{"%1"}.arg(value,
                                                                         mFieldWidth,
                                                                         mFormat.toLatin1(),
                                                                         mPrecision,
                                                                         mFillChar);

                                            } else if (arrayValuesItemObject["value"].isString()) {
                                                text = arrayValuesItemObject["value"].toString();
                                            }
                                            setValue(text);
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
 * getDstUnits
 * Returns the destination units
 */
    QString DisplayBase::getDstUnits() const {
        return mDstUnits;
    }

/*
 * getSrcUnits
 * Returns the source units
 */
    QString DisplayBase::getSrcUnits() const {
        return mSrcUnits;
    }

/*
 * getFullPath
 * Returns the full path
 */
    QString DisplayBase::getFullPath() const {
        return mFullPath;
    }

/*
 * getDescription
 * Returns the description
 */
    QString DisplayBase::getDescription() const {
        return mDescription;
    }

/*
 * getFillChar
 * Returns the fill char
 */
    QChar DisplayBase::getFillChar() const {
        return mFillChar;
    }

/*
 * getFormat
 * Returns the format
 */
    QChar DisplayBase::getFormat() const {
        return mFormat;
    }

/*
 * getPrecision
 * Get the used precision
 */
    int DisplayBase::getPrecision() const {
        return mPrecision;
    }

/*
 * getFieldWidth
 * Get the display's width
 */
    int DisplayBase::getFieldWidth() const {
        return mFieldWidth;
    }

/*
 * setDstUnits
 * Sets the destination units
 */
    void DisplayBase::setDstUnits(QString &dstUnits) {
        mDstUnits = dstUnits;
    }

/*
 * setSrcUnits
 * Sets the source units
 */
    void DisplayBase::setSrcUnits(QString &srcUnits) {
        mSrcUnits = srcUnits;
    }

/*
 * setDescription
 * Sets the description
 */
    void DisplayBase::setDescription(QString &description) {
        mDescription = description;
    }

/*
 * setFillChar
 * Sets the fill char
 */
    void DisplayBase::setFillChar(QChar fillChar) {
        mFillChar = fillChar;
    }

/*
 * setFormat
 * Sets th format
 */
    void DisplayBase::setFormat(QChar format) {
        mFormat = format;
    }

/*
 * setPrecision
 * Sets the precision
 */
    void DisplayBase::setPrecision(int precision) {
        mPrecision = precision;
    }

/*
 * setFieldWidth
 * Sets the display's width
 */
    void DisplayBase::setFieldWidth(int fieldWidth) {
        mFieldWidth = fieldWidth;
    }
}