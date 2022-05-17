//
// Created by Raffaele Montella on 31/01/22.
//

#ifndef FAIRWIND_RESULTITEM_HPP
#define FAIRWIND_RESULTITEM_HPP

#include <QWidget>
#include <QJsonObject>

namespace fairwind::apps::portolano {
    QT_BEGIN_NAMESPACE
    namespace Ui { class ResultItem; }
    QT_END_NAMESPACE

    class ResultItem : public QWidget {
    Q_OBJECT

    public:
    explicit ResultItem(QWidget *parent = nullptr, QJsonObject feature = QJsonObject());

        ~ResultItem() override;

    public slots:

        void updateNavigationPosition(const QJsonObject update);
        void updateNavigationSpeedOverGround(const QJsonObject update);

    private:
        Ui::ResultItem *ui;
        QGeoCoordinate mPosition;
        QJsonObject mFeature;

        void updateNavigationData(const QJsonObject update);
    };
} // fairwind::apps::portolano

#endif //FAIRWIND_RESULTITEM_HPP
