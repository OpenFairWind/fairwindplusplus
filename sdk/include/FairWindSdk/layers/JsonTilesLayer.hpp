#ifndef JSONTILESLAYER_HPP
#define JSONTILESLAYER_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QGeoView/QGVLayerJsonTiles.h>
#include <FairWindSdk/ILayer.hpp>

namespace fairwind::layers {
    class FAIRWINDSDK_LIB_DECL JsonTilesLayer : public QGVLayerJsonTiles, public fairwind::layers::ILayer {
    Q_OBJECT

    public:
        explicit JsonTilesLayer();

        ~JsonTilesLayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        virtual ILayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:


    };
}

#endif // JSONTILESLAYER_HPP
