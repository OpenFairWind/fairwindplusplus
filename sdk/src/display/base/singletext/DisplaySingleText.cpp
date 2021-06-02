//
// Created by Raffaele Montella on 22/04/21.
//

#include "ui_DisplaySingleText.h"

#include <FairWindSdk/DisplaySingleText.hpp>
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/util/Units.hpp>
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

    int size= contentsRect().height();

    QFont newFontLabel("Arial",size*0.25);
    ui->label_Label->setFont(newFontLabel);

    QFont newFontUnits("Arial",size*0.25);
    ui->label_Units->setFont(newFontUnits);

    QFont newFontValue("Arial",size*0.75);
    ui->label_Value1->setFont(newFontValue);

}

DisplaySingleText::~DisplaySingleText() {
    delete ui;
}

QImage DisplaySingleText::getIcon() const {
    return QImage(":resources/images/icons/signalk_icon.png");
}

QWidget *DisplaySingleText::onSettings() {
    return nullptr;
}

void DisplaySingleText::onInit(QMap<QString, QVariant> params) {
    qDebug() << "DisplaySingleText::onInit(" << params << ")";

    if (params.contains("fullPath")) {
        subscribe(params["fullPath"].toString());
    }
    if (params.contains("label")) {
        setLabel(params["label"].toString());
    }
    if (params.contains("units")) {
        setUnits(params["units"].toString());
    }
    if (params.contains("text")) {
        setText(params["text"].toString());
    }
}

fairwind::displays::IFairWindDisplay *DisplaySingleText::getNewInstance() {
    return static_cast<IFairWindDisplay *>(new DisplaySingleText());
}

void DisplaySingleText::setLabel(QString label) {
    ui->label_Label->setText(label);
}

void DisplaySingleText::setUnits(QString units) {
    ui->label_Units->setText(units);
}

void DisplaySingleText::setText(QString text) {
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
                        QString text="";
                        for (int i=0;i<mFieldWidth;i++) {
                            text=text+"0";
                        }
                        setText(text);
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
                                                    mSrcUnits,mUnits,
                                                    arrayValuesItemObject["value"].toDouble());


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

QString DisplaySingleText::getClassName() const {
    return this->metaObject()->className();
}

bool DisplaySingleText::smaller() {
    ui->label_Label->setFont(QFont("Arial",ui->label_Label->font().pixelSize()-1));
    ui->label_Units->setFont(QFont("Arial",ui->label_Units->font().pixelSize()-1));
    ui->label_Value1->setFont(QFont("Arial",ui->label_Value1->font().pixelSize()-1));
    return isVisible();
}

bool DisplaySingleText::bigger() {
    ui->label_Label->setFont(QFont("Arial",ui->label_Label->font().pixelSize()+1));
    ui->label_Units->setFont(QFont("Arial",ui->label_Units->font().pixelSize()+1));
    ui->label_Value1->setFont(QFont("Arial",ui->label_Value1->font().pixelSize()+1));
    return isVisible();
}