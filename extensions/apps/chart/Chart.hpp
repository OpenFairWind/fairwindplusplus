//
// Created by Raffaele Montella on 05/04/21.
//

#ifndef FAIRWIND_CHART_HPP
#define FAIRWIND_CHART_HPP


#include <QObject>
#include <QtPlugin>

#include "../../../include/IFairWindApp.hpp"
#include "../../../include/FairWindApp.hpp"


namespace fairwind::extensions::apps::chart {
    class Chart : public QObject, /*FairWindApp,*/ IFairWindApp {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID IID_FAIRWIND_APPS FILE "manifest.json")
        Q_INTERFACES(fairwind::extensions::apps::IFairWindApp)

    public:
        [[nodiscard]] QString getUUID()   override;
        [[nodiscard]] QString getId()  override;
        [[nodiscard]] QString getName()  override;
        [[nodiscard]] QString getDesc()  override ;
        void setMetaData(QJsonObject &metaData) override;
        [[nodiscard]] QImage getIcon()  override;

        QWidget *onGui(QMainWindow *mainWindow, QMap<QString, QString> args) override;

    private:
        QWidget *m_widgetMapApp= nullptr;
        QJsonObject m_metaData;
    };
}


#endif //FAIRWIND_CHART_HPP
