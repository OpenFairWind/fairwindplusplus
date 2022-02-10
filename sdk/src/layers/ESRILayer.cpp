#include "layers/ESRILayer.hpp"

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
    // Shapefile extension accepts only absolute path, not qt resource files
    const auto sourcePath = getRealPathToSource(shapeFile, shxPath);

    if (sourcePath.isEmpty()) {
        return;
    }

    setSourceFileName(sourcePath);
    activate();
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

QString fairwind::layers::ESRILayer::getRealPathToSource(const QString& shpFile, const QString& shxFile)
{
    QTemporaryDir tempDir;
    if (!tempDir.isValid()) {
        return "";
    }

    QFileInfo shapeFileInfo(shpFile), shxFileInfo(shxFile);
    if (!shapeFileInfo.exists() || !shxFileInfo.exists()) {
        return "";
    }

    const QString shapeFileName = shapeFileInfo.fileName();
    const QString shxFileName = shxFileInfo.fileName();

    const QString tempShapeFileName = tempDir.path() + shapeFileName;
    const QString tempShxFileName = tempDir.path() + shxFileName;

    if (QFile::copy(shpFile, tempShapeFileName) &&
            QFile::copy(shxFile, tempShxFileName)) {
        return tempShapeFileName;
    }

    return "";
}
