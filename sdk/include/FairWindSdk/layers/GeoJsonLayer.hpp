#ifndef GEOJSONLAYER_HPP
#define GEOJSONLAYER_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QGeoView/QGVLayerGeoJson.h>
#include <FairWindSdk/ILayer.hpp>

namespace fairwind::layers {
    class FAIRWINDSDK_LIB_DECL GeoJsonLayer : public QGVLayerGeoJson, public fairwind::layers::ILayer {
    Q_OBJECT

    public:
        explicit GeoJsonLayer();

        ~GeoJsonLayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        virtual ILayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:


    };
}

#endif // GEOJSONLAYER_HPP
