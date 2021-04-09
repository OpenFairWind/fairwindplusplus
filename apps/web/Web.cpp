//
// Created by Raffaele Montella on 01/04/21.
//

#include "Web.hpp"
#include "WebView.hpp"

#include <QWebEngineSettings>
#include <QWebEngineProfile>

#include <QDebug>
#include <QPushButton>
#include <QAbstractButton>
#include <QHBoxLayout>


QImage fairwind::apps::web::Web::getIcon() const {
    return QImage(":/resources/images/icons/web_icon.png");
}

QWidget *fairwind::apps::web::Web::onGui(QMainWindow *mainWindow, QMap<QString, QString> args) {


    if (args.find("Url")!=args.end()) {
        m_url = args["Url"];

        m_widgetWebApp = new QWidget();

        auto *webView = new WebView(m_widgetWebApp);
        webView->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

        auto *widgetWebApp_Buttons = new QWidget(m_widgetWebApp);

        auto *pushButton_Home = new QPushButton(widgetWebApp_Buttons);
        pushButton_Home->setText("Home");

        connect(pushButton_Home, &QPushButton::clicked, this, &fairwind::apps::web::Web::toolButton_home_clicked);

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



void fairwind::apps::web::Web::toolButton_home_clicked() {
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget)
        return;

    ((WebView *)(m_widgetWebApp->children()[0]))->load(QUrl(m_url));
}


QString fairwind::apps::web::Web::getId() const {
    return fairwind::FairWindAppBase::getId();
}

QString fairwind::apps::web::Web::getName() const {
    return fairwind::FairWindAppBase::getName();
}

QString fairwind::apps::web::Web::getDesc() const {
    return fairwind::FairWindAppBase::getDesc();
}

void fairwind::apps::web::Web::init(QJsonObject *metaData) {
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif
    m_profile = QWebEngineProfile::defaultProfile();
    FairWindAppBase::init(metaData);
}