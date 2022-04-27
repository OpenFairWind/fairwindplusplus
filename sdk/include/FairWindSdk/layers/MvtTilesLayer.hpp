#ifndef MVTTILESLAYER_HPP
#define MVTTILESLAYER_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QGeoView/QGVMvtLayerTiles.h>
#include <FairWindSdk/ILayer.hpp>

namespace fairwind::layers {
    class FAIRWINDSDK_LIB_DECL MvtTilesLayer : public QGVMvtLayerTiles, public fairwind::layers::ILayer {
    Q_OBJECT

    public:
        explicit MvtTilesLayer();

        ~MvtTilesLayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        virtual ILayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:


    };
}

#endif // MVTTILESLAYER_HPP
