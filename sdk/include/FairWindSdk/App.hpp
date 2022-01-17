//
// Created by Raffaele Montella on 27/03/21.
//

#ifndef FAIRWINDS_APP_HPP
#define FAIRWINDS_APP_HPP

#include <QMap>

#include "FairWindSDK.hpp"
#include "IFairWindApp.hpp"

namespace fairwind {
    class FAIRWINDSDK_LIB_DECL App: QObject {
    Q_OBJECT
    public:
    App();

    App(apps::FairWindApp *fairWindApp, bool active=true, int order=1);

    App(const App &app);

    QString getHash();
    QString getExtension();
    bool getActive();
    void setActive(bool active);
    int getOrder();
    void setOrder(int order);
    QString getName();
    QString getDesc();
    QString getVersion();
    QString getVendor();
    QString getCopyright();
    QString getLicense();
    QImage getIcon();
    QString getRoute();
    QMap<QString, QVariant> getArgs();

    private:
    void generateHash();

    QString m_hash;
    QString m_extension;
    bool m_active;
    int m_order;
    QString m_name;
    QString m_desc;
    QString m_version;
    QString m_vendor;
    QString m_copyright;
    QString m_license;
    QImage m_icon;
    QString m_route;
    QMap<QString, QVariant> m_args;
};
}

#endif //FAIRWINDS_APP_HPP