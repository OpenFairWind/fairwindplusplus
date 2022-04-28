#include "layers/MvtTilesLayer.hpp"

fairwind::layers::MvtTilesLayer::MvtTilesLayer() :
    QGVMvtLayerTiles(256, "")
{
    setName("MVT Layer Tiles");
    setDescription("Integrates a layer tiles with MVT format on the map.");
}

fairwind::layers::MvtTilesLayer::~MvtTilesLayer() {}

QImage fairwind::layers::MvtTilesLayer::getIcon() const
{
    return QImage(":/resources/images/icons/layer-geojson-icon.png");;
}

void fairwind::layers::MvtTilesLayer::onInit(QMap<QString, QVariant> params)
{
    // Set the layer's name from the parameters
    if (params.contains("name")) {
        setName(params["name"].toString());
    }

    // Set the layer's description from the parameters
    if (params.contains("description")) {
        setDescription(params["description"].toString());
    }

    if (!params.contains("api_url") || !params.contains("api_key")) {
        qDebug() << "Unable to create" << getName() << ". Api URL or Api Key missing.";
        setVisible(false);
        return;
    }

    if (!params.contains("tile_type")) {
        qDebug() << "Unable to create" << getName() << ". Tile Type missing.";
        setVisible(false);
        return;
    }

    const auto apiUrl = params.value("api_url").toString();
    const auto apiKey = params.value("api_key").toString();
    const auto tileType = params.value("tile_type").toString();

    setUrl(apiUrl);
    setApiKey(apiKey);
    setTileType(tileType);
}

fairwind::layers::ILayer *fairwind::layers::MvtTilesLayer::getNewInstance()
{
    return static_cast<ILayer *>(new MvtTilesLayer());
}

QWidget *fairwind::layers::MvtTilesLayer::onLegenda()
{
    return nullptr;
}

QWidget *fairwind::layers::MvtTilesLayer::onSettings()
{
    return nullptr;
}

QString fairwind::layers::MvtTilesLayer::getClassName() const
{
    return this->metaObject()->className();
}


