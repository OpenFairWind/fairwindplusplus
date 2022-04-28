#include "layers/JsonTilesLayer.hpp"

fairwind::layers::JsonTilesLayer::JsonTilesLayer() :
    QGVLayerJsonTiles(256, "")
{
    setName("JSON Layer Tiles");
    setDescription("Integrates a geojson layer tiles on the map.");
}

fairwind::layers::JsonTilesLayer::~JsonTilesLayer() {}

QImage fairwind::layers::JsonTilesLayer::getIcon() const
{
    return QImage(":/resources/images/icons/layer-geojson-icon.png");;
}

void fairwind::layers::JsonTilesLayer::onInit(QMap<QString, QVariant> params)
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

fairwind::layers::ILayer *fairwind::layers::JsonTilesLayer::getNewInstance()
{
    return static_cast<ILayer *>(new JsonTilesLayer());
}

QWidget *fairwind::layers::JsonTilesLayer::onLegenda()
{
    return nullptr;
}

QWidget *fairwind::layers::JsonTilesLayer::onSettings()
{
    return nullptr;
}

QString fairwind::layers::JsonTilesLayer::getClassName() const
{
    return this->metaObject()->className();
}


