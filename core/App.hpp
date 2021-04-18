//
// Created by Raffaele Montella on 27/03/21.
//

#ifndef FAIRWINDS_APP_HPP
#define FAIRWINDS_APP_HPP


#include <QMap>
#include "../include/IFairWindApp.hpp"

namespace fairwind {
    class App: QObject {
        Q_OBJECT
    public:
        App();

        App(apps::IFairWindApp *fairWindApp, QMap<QString, QString> args, bool active=true, int order=1);

        App(const App &app);

        QString getHash();
        QString getExtension();
        bool getActive();
        void setActive(bool active);
        int getOrder();
        void setOrder(int order);
        QString getName();
        QImage getIcon();
        QMap<QString, QString> getArgs();

        bool isPlugin();

    private:
        void generateHash();


        QString m_hash;
        QString m_extension;
        bool m_active;
        int m_order;
        QString m_name;
        QString m_desc;
        QImage m_icon;
        QMap<QString,QString> m_args;
    };

}

#endif //FAIRWINDS_APP_HPP
