#include "layers/ESRILayer.hpp"

#include "QGeoView/QGVLayerFile.h"

#include <QTemporaryDir>

fairwind::layers::ESRILayer::ESRILayer() :
    QGVLayerESRI(nullptr, "")
{
    setName("ESRI Shapefile layer");
    setDescription("Integrates an ESRI layer on the map.");
}

fairwind::layers::ESRILayer::~ESRILayer() {}

QImage fairwind::layers::ESRILayer::getIcon() const
{
    return QImage(":/resources/images/icons/layer-esri-icon.png");;
}

void fairwind::layers::ESRILayer::onInit(QMap<QString, QVariant> params)
{
    // Set the layer's name from the parameters
    if (params.contains("name")) {
        setName(params["name"].toString());
    }

    // Set the layer's description from the parameters
    if (params.contains("description")) {
        setDescription(params["description"].toString());
    }

    if (!params.contains("shapefile") || !params.contains("shxfile")) {
        return;
    }

    const auto shapeFile = params.value("shapefile").toString();
    const auto shxPath = params.value("shxfile").toString();

    QString sourcePath{}, shxSource{};
    if (QGVLayerFile::resourceToDisk(shapeFile, sourcePath) &&
            QGVLayerFile::resourceToDisk(shxPath, shxSource)) {
        qDebug() << "ESRILayer loading" << sourcePath;
        setSourceFileName(sourcePath);
        activate();
    } else {
        qDebug() << "ESRILayer unable to load" << shapeFile;
    }
}

fairwind::layers::ILayer *fairwind::layers::ESRILayer::getNewInstance()
{
    return static_cast<ILayer *>(new ESRILayer());
}

QWidget *fairwind::layers::ESRILayer::onLegenda()
{
    return nullptr;
}

QWidget *fairwind::layers::ESRILayer::onSettings()
{
    return nullptr;
}

QString fairwind::layers::ESRILayer::getClassName() const
{
    return this->metaObject()->className();
}
