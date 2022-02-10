#include "layers/GeoJsonLayer.hpp"

fairwind::layers::GeoJsonLayer::GeoJsonLayer() :
    // Dopo il pull il getParent() può essere eliminato
    QGVLayerGeoJson(getParent(), "")
{
    setName("Geo Json Layer");
    setDescription("Integrates a geojson layer on the map.");
}

fairwind::layers::GeoJsonLayer::~GeoJsonLayer() {}

QImage fairwind::layers::GeoJsonLayer::getIcon() const
{
    // Da modificare
    return QImage(":resources/images/icons/layer_osm_icon.png");;
}

void fairwind::layers::GeoJsonLayer::onInit(QMap<QString, QVariant> params)
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
    setSourceFileName(sourcePath);
    qDebug() << "GeoJsonLayer onInit(): " << getSourceFileName();
    activate();
}

fairwind::layers::ILayer *fairwind::layers::GeoJsonLayer::getNewInstance()
{
    return static_cast<ILayer *>(new GeoJsonLayer());
}

QWidget *fairwind::layers::GeoJsonLayer::onLegenda()
{
    return nullptr;
}

QWidget *fairwind::layers::GeoJsonLayer::onSettings()
{
    return nullptr;
}

QString fairwind::layers::GeoJsonLayer::getClassName() const
{
    return this->metaObject()->className();
}
