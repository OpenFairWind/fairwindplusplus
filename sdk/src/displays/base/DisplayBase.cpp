//
// Created by Raffaele Montella on 05/06/21.
//


#include <QJsonValue>
#include <QJsonArray>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/util/Units.hpp>
#include "FairWindSdk/displays/DisplayBase.hpp"

fairwind::displays::DisplayBase::DisplayBase() {
    mFormat=QChar('f');
    mFillChar=QChar('0');
    mPrecision=1;
    mFieldWidth=3;
    mDstUnits="";
}

fairwind::displays::DisplayBase::~DisplayBase() {

}

void fairwind::displays::DisplayBase::subscribe(QString fullPath) {

    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    mFullPath=fullPath.replace("${self}",signalKDocument->getSelf());
    qDebug() << "DisplayBase::subscribe: " << mFullPath;

    QJsonValue jsonValue=signalKDocument->subtree(mFullPath);
    if (jsonValue.isObject()) {
        QJsonObject jsonObject=jsonValue.toObject();
        if (jsonObject.contains("meta") && jsonObject["meta"].isObject()) {
            QJsonObject objectMeta=jsonObject["meta"].toObject();
            if (objectMeta.contains("units") && objectMeta["units"].isString()) {
                mSrcUnits=objectMeta["units"].toString();
            }
            if (objectMeta.contains("description") && objectMeta["description"].isString()) {
                mDescription=objectMeta["description"].toString();
            }
        }
        auto parts=mFullPath.split(".");
        parts.removeFirst();
        parts.removeFirst();
        auto key=parts.join(".");

        qDebug() << "DisplaySingleText::subscribe: key" << key;
        auto config=fairWind->getConfig();
        if (config.contains("SignalK") && config["SignalK"].isObject()) {
            QJsonObject objectSignalK=config["SignalK"].toObject();
            if (objectSignalK.contains("keys") && objectSignalK["keys"].isObject()) {
                QJsonObject objectKeys=objectSignalK["keys"].toObject();
                if (objectKeys.contains(key) && objectKeys[key].isObject()) {
                    QJsonObject objectKey=objectKeys[key].toObject();
                    if (objectKey.contains("label") && objectKey["label"].isString()) {
                        setLabel(objectKey["label"].toString());
                    }
                    if (objectKey.contains("format") && objectKey["format"].isString()) {
                        mFormat=objectKey["format"].toString().at(0);
                    }
                    if (objectKey.contains("precision") && objectKey["precision"].isDouble()) {
                        mPrecision=objectKey["precision"].toDouble();
                    }
                    if (objectKey.contains("fieldWidth") && objectKey["fieldWidth"].isDouble()) {
                        mFieldWidth=objectKey["fieldWidth"].toDouble();
                        QString text="";
                        for (int i=0;i<mFieldWidth;i++) {
                            text=text+"0";
                        }
                        setValue(text);
                    }
                    if (objectKey.contains("fillChar") && objectKey["fillChar"].isString()) {
                        mFillChar=objectKey["fillChar"].toString().at(0);
                    }
                    if (objectKey.contains("units") && objectKey["units"].isString()) {
                        mDstUnits=objectKey["units"].toString();
                        setUnits(fairwind::Units::getInstance()->getLabel(mDstUnits));
                    }
                }
            }
        }

        if (jsonObject.contains("value") && jsonObject["value"].isDouble()) {
            QString text="__.__";
            if (jsonObject["value"].isDouble()) {


                double value=fairwind::Units::getInstance()->convert(
                        mSrcUnits,mDstUnits,
                        jsonObject["value"].toDouble());


                text=QString{ "%1" }.arg(value,
                                         mFieldWidth,
                                         mFormat.toLatin1(),
                                         mPrecision,
                                         mFillChar );

            } else if (jsonObject["value"].isString()) {
                text = jsonObject["value"].toString();
            }
            setValue(text);
        }
    }
}

void fairwind::displays::DisplayBase::update(const QJsonObject update) {
    if (update.contains("updates") && update["updates"].isArray()) {
        QJsonArray arrayUpdates=update["updates"].toArray();
        if (arrayUpdates.size()==1) {
            QJsonValue arrayUpdatesItem=arrayUpdates[0];
            if (arrayUpdatesItem.isObject()) {
                QJsonObject arrayUpdatesItemObject=arrayUpdatesItem.toObject();
                if (arrayUpdatesItemObject.contains("values") && arrayUpdatesItemObject["values"].isArray()) {
                    QJsonArray arrayValues = arrayUpdatesItemObject["values"].toArray();
                    for (auto arrayValuesItem: arrayValues) {
                        if (arrayValuesItem.isObject()) {
                            QJsonObject arrayValuesItemObject = arrayValuesItem.toObject();
                            if (arrayValuesItemObject.contains("path") && arrayValuesItemObject["path"].isString()) {
                                QString path = arrayValuesItemObject["path"].toString();

                                if (mFullPath.endsWith(path)) {
                                    //qDebug() << "DisplaySingleText::path:" << path;
                                    if (arrayValuesItemObject.contains("value")) {

                                        QString text="__.__";
                                        if (arrayValuesItemObject["value"].isDouble()) {


                                            double value=fairwind::Units::getInstance()->convert(
                                                    mSrcUnits, mDstUnits,
                                                    arrayValuesItemObject["value"].toDouble());


                                            text=QString{ "%1" }.arg(value,
                                                                     mFieldWidth,
                                                                     mFormat.toLatin1(),
                                                                     mPrecision,
                                                                     mFillChar );

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

QString fairwind::displays::DisplayBase::getDstUnits() const {
    return mDstUnits;
}

QString fairwind::displays::DisplayBase::getSrcUnits() const {
    return mSrcUnits;
}



QString fairwind::displays::DisplayBase::getFullPath() const {
    return mFullPath;
}

QString fairwind::displays::DisplayBase::getDescription() const {
    return mDescription;
}

QChar fairwind::displays::DisplayBase::getFillChar() const {
    return mFillChar;
}

QChar fairwind::displays::DisplayBase::getFormat() const {
    return mFormat;
}

int fairwind::displays::DisplayBase::getPrecision() const {
    return mPrecision;
}

int fairwind::displays::DisplayBase::getFieldWidth() const {
    return mFieldWidth;
}

void fairwind::displays::DisplayBase::setDstUnits(QString &dstUnits) {
    mDstUnits=dstUnits;
}

void fairwind::displays::DisplayBase::setSrcUnits(QString &srcUnits) {
    mSrcUnits=srcUnits;
}

void fairwind::displays::DisplayBase::setDescription(QString &description) {
    mDescription=description;
}

void fairwind::displays::DisplayBase::setFillChar(QChar fillChar) {
    mFillChar=fillChar;
}

void fairwind::displays::DisplayBase::setFormat(QChar format) {
    mFormat=format;
}

void fairwind::displays::DisplayBase::setPrecision(int precision) {
    mPrecision=precision;
}

void fairwind::displays::DisplayBase::setFieldWidth(int fieldWidth) {
    mFieldWidth=fieldWidth;
}


