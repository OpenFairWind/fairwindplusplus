//
// Created by Raffaele Montella on 16/07/21.
//

#ifndef FAIRWIND_CONNECTIONS_HPP
#define FAIRWIND_CONNECTIONS_HPP

#include <QWidget>
#include <FairWindSdk/ISettings.hpp>

namespace Ui {
    class Connections;
}

namespace fairwind::ui::settings::connections {

    class Connections : public QWidget, public ISettings {
        Q_OBJECT

    public:
        explicit Connections(QWidget *parent = 0);

        ~Connections();

        QString getClassName() const override;
        QImage getIcon() const override;
        QString getName() const override;
        ISettings *getNewInstance() override;

    protected :
        void showEvent(QShowEvent *event) override;

    private:
        Ui::Connections *ui;
    };
}

#endif //FAIRWIND_CONNECTIONS_HPP
