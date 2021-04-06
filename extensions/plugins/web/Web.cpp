//
// Created by Raffaele Montella on 01/04/21.
//

#include "Web.hpp"
#include "WebView.hpp"
#include "../../../ui/MainWindow.hpp"

#include <QDebug>
#include <QPushButton>
#include <QAbstractButton>
#include <QHBoxLayout>


QImage fairwind::extensions::plugins::web::Web::getIcon() const {
    return QImage(":/resources/images/icons/web_icon.png");
}

QString fairwind::extensions::plugins::web::Web::getId() const {
    return FairWindExtension::getId();
}

QString fairwind::extensions::plugins::web::Web::getName() const {
    return FairWindExtension::getName();
}

QString fairwind::extensions::plugins::web::Web::getDesc() const {
    return FairWindExtension::getDesc();
}

void fairwind::extensions::plugins::web::Web::setMetaData(QJsonObject &metaData) {
    FairWindExtension::setMetaData(metaData);
}

QWidget *fairwind::extensions::plugins::web::Web::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {


    if (args.find("Url")!=args.end()) {
        m_url = args["Command"];

        m_widgetWebApp = new QWidget();

        auto *webView = new WebView(m_widgetWebApp);
        webView->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

        auto *widgetWebApp_Buttons = new QWidget(m_widgetWebApp);

        auto *pushButton_Home = new QPushButton(widgetWebApp_Buttons);
        pushButton_Home->setText("Home");

        connect(pushButton_Home, &QPushButton::clicked, this, &fairwind::extensions::plugins::web::Web::toolButton_home_clicked);

        auto *pushButton_Prev = new QPushButton(widgetWebApp_Buttons);
        pushButton_Prev->setText("<");

        auto *pushButton_Next = new QPushButton(widgetWebApp_Buttons);
        pushButton_Next->setText(">");

        auto *hBoxLayout = new QHBoxLayout();
        m_widgetWebApp->setLayout(hBoxLayout);
        hBoxLayout->addWidget(webView);
        hBoxLayout->addWidget(widgetWebApp_Buttons);

        auto *vBoxLayout = new QVBoxLayout();
        vBoxLayout->setAlignment(Qt::AlignTop);
        vBoxLayout->addWidget(pushButton_Home);
        vBoxLayout->addWidget(pushButton_Prev);
        vBoxLayout->addWidget(pushButton_Next);
        widgetWebApp_Buttons->setLayout(vBoxLayout);

        webView->load(QUrl(m_url));
    }
    return m_widgetWebApp;
}



void fairwind::extensions::plugins::web::Web::toolButton_home_clicked() {
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget)
        return;

    ((WebView *)(m_widgetWebApp->children()[0]))->load(QUrl(m_url));
}
