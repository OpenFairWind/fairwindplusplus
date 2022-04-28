#ifdef USE_GDAL_FEATURES

#include "layers/TiffLayer.hpp"

#include "QGeoView/QGVLayerFile.h"

fairwind::layers::TiffLayer::TiffLayer() :
    QGVRasterLayer(nullptr, "")
{
    setName("Geo Json Layer");
    setDescription("Integrates a geojson layer on the map.");
}

fairwind::layers::TiffLayer::~TiffLayer() {}

QImage fairwind::layers::TiffLayer::getIcon() const
{
    return QImage(":/resources/images/icons/layer-geojson-icon.png");;
}

void fairwind::layers::TiffLayer::onInit(QMap<QString, QVariant> params)
{
    // Set the layer's name from the parameters
    if (params.contains("name")) {
        setName(params["name"].toString());
    }

    // Set the layer's description from the parameters
    if (params.contains("description")) {
        setDescription(params["description"].toString());
    }

    if (!params.contains("sourcepath")) {
        return;
    }

    const auto sourcePath = params.value("sourcepath").toString();
    QString tempSourcePath{};

    if (QGVLayerFile::resourceToDisk(sourcePath, tempSourcePath)) {
        qDebug() << "TiffLayer loading" << tempSourcePath;
        setSourceFileName(tempSourcePath);
        activate();
    } else {
        qDebug() << "TiffLayer unable to load" << sourcePath;
    }
}

fairwind::layers::ILayer *fairwind::layers::TiffLayer::getNewInstance()
{
    return static_cast<ILayer *>(new TiffLayer());
}

QWidget *fairwind::layers::TiffLayer::onLegenda()
{
    return nullptr;
}

QWidget *fairwind::layers::TiffLayer::onSettings()
{
    return nullptr;
}

QString fairwind::layers::TiffLayer::getClassName() const
{
    return this->metaObject()->className();
}

#endif
