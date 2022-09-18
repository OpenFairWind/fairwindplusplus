#ifndef TIFFLAYER_HPP
#define TIFFLAYER_HPP



#include <FairWindSdk/FairWindSDK.hpp>
#include <QGeoView/QGVRasterLayer.h>
#include <FairWindSdk/ILayer.hpp>

namespace fairwind::layers {
    class FAIRWINDSDK_LIB_DECL TiffLayer : public QGVRasterLayer, public fairwind::layers::ILayer {
    Q_OBJECT

    public:
        explicit TiffLayer();

        ~TiffLayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        virtual ILayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:


    };
}

#endif // TIFFLAYER_HPP
