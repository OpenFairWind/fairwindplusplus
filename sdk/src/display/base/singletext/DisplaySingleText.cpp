//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplaySingleText.h"

#include <FairWindSdk/DisplaySingleText.hpp>
#include <DisplaySingleText.hpp>
#include <FairWindSdk/FairWind.hpp>
#include <QJsonArray>


DisplaySingleText::DisplaySingleText(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::DisplaySingleText) {
    ui->setupUi(this);
    mFormat=QChar('f');
    mFillChar=QChar('0');
    mPrecision=1;
    mFieldWidth=3;
    mUnits="";
}

DisplaySingleText::~DisplaySingleText() {
    delete ui;
}

void DisplaySingleText::setLabel(QString label) {

    int size= contentsRect().height()*0.25;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Label->setFont(newFont);        //Set the new font with new size
    ui->label_Label->setText(label);
}

void DisplaySingleText::setUnits(QString label) {

    int size= contentsRect().height()*0.25;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Units->setFont(newFont);        //Set the new font with new size
    ui->label_Units->setText(label);
}

void DisplaySingleText::setText(QString text) {
    int size= contentsRect().height()*0.75;
    QFont newFont("Arial",size);
    QFontMetrics nfm(newFont);
    ui->label_Value1->setFont(newFont);        //Set the new font with new size
    ui->label_Value1->setText(text);
}

void DisplaySingleText::subscribe(QString fullPath) {

    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

    mFullPath=fullPath.replace("${self}",signalKDocument->getSelf());
    qDebug() << "DisplaySingleText::subscribe: " << mFullPath;

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

        //qDebug() << "DisplaySingleText::subscribe: key" << key;
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
                    }
                    if (objectKey.contains("fillChar") && objectKey["fillChar"].isString()) {
                        mFillChar=objectKey["fillChar"].toString().at(0);
                    }
                    if (objectKey.contains("units") && objectKey["units"].isString()) {
                        mUnits=objectKey["units"].toString();
                    }

                    if (objectSignalK.contains("units") && objectSignalK["units"].isObject()) {
                        QJsonObject objectUnits=objectSignalK["units"].toObject();

                        if (objectUnits.contains(mUnits) && objectUnits[mUnits].isObject()) {
                            QJsonObject objectUnit=objectUnits[mUnits].toObject();
                            if (objectUnit.contains("label") && objectUnit["label"].isString()) {
                                QString label=objectUnit["label"].toString();
                                setUnits(label);
                            }


                            if (!mSrcUnits.isEmpty()) {
                                if (objectUnits.contains(mSrcUnits) && objectUnits[mUnits].isObject()) {
                                    QJsonObject objectSrcUnits=objectUnits[mUnits].toObject();
                                    if (objectSrcUnits.contains(mUnits) && objectSrcUnits[mUnits].isDouble()) {
                                        mConversionFactor=objectSrcUnits[mUnits].toDouble();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (jsonObject.contains("value") && jsonObject["value"].isDouble()) {
            // Preset the value
        }
    }

    signalKDocument->subscribe( mFullPath,
            this,SLOT(DisplaySingleText::update));
}

void DisplaySingleText::update(const QJsonObject update) {
    //qDebug() << "DisplaySingleText::update:" << update;
    auto fairWind = fairwind::FairWind::getInstance();
    auto signalKDocument = fairWind->getSignalKDocument();

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

                                            double value=arrayValuesItemObject["value"].toDouble();

                                            if (mSrcUnits=="rad") {
                                                value = value*57.2958;
                                            } else if (mSrcUnits=="m/s") {
                                                value = value*1.94384;
                                            }


                                            text=QString{ "%1" }.arg(value,
                                                                     mFieldWidth,
                                                                     mFormat.toLatin1(),
                                                                     mPrecision,
                                                                     mFillChar );

                                        } else if (arrayValuesItemObject["value"].isString()) {
                                            text = arrayValuesItemObject["value"].toString();
                                        }
                                        setText(text);
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
