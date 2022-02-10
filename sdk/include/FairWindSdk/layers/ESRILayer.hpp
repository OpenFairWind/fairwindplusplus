#ifndef ESRILAYER_HPP
#define ESRILAYER_HPP

#include <FairWindSdk/FairWindSDK.hpp>
#include <QGeoView/QGVLayerESRI.h>
#include <FairWindSdk/ILayer.hpp>

namespace fairwind::layers {
    class FAIRWINDSDK_LIB_DECL ESRILayer : public QGVLayerESRI, public fairwind::layers::ILayer {
    Q_OBJECT

    public:
        explicit ESRILayer();

        ~ESRILayer();

        QString getClassName() const override;

        QImage getIcon() const override;

        void onInit(QMap<QString, QVariant> params) override;

        virtual ILayer *getNewInstance() override;

        QWidget *onLegenda() override;

        QWidget *onSettings() override;

    private:

        QString getRealPathToSource(const QString&, const QString&);
    };
}

#endif // ESRILAYER_HPP
