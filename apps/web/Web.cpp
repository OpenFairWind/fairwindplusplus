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
#include <FairWindSdk/FairWind.hpp>


QString fairwind::apps::web::Web::getId() const {
    return fairwind::AppBase::getId();
}

QString fairwind::apps::web::Web::getName() const {
    return fairwind::AppBase::getName();
}

QString fairwind::apps::web::Web::getDesc() const {
    return fairwind::AppBase::getDesc();
}

QString fairwind::apps::web::Web::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString fairwind::apps::web::Web::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString fairwind::apps::web::Web::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString fairwind::apps::web::Web::getLicense() const {
    return fairwind::AppBase::getLicense();
}

QImage fairwind::apps::web::Web::getIcon() const {
    return QImage(":/resources/images/icons/web_icon.png");
}

void fairwind::apps::web::Web::onInit(QJsonObject *metaData) {
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif
    m_profile = QWebEngineProfile::defaultProfile();
    AppBase::onInit(metaData);

    auto fairWind = fairwind::FairWind::getInstance();

    m_url = "http://fairwind.uniparthenope.it";
}

QWidget *fairwind::apps::web::Web::onGui(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    if (args.contains("Url")) {
        m_url = args["Url"].toString();
    }

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

    return m_widgetWebApp;
}



void fairwind::apps::web::Web::toolButton_home_clicked() {
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget)
        return;

    ((WebView *)(m_widgetWebApp->children()[0]))->load(QUrl(m_url));
}


QWidget *fairwind::apps::web::Web::onSettings(QTabWidget *tabWidgets) {
    return nullptr;
}

QJsonObject fairwind::apps::web::Web::getConfig() {
    return AppBase::getConfig();
}

QJsonObject fairwind::apps::web::Web::getMetaData() {
    return AppBase::getMetaData();
}

void fairwind::apps::web::Web::updateSettings(QString settingsID, QString newValue) {
    QDir appDataPath = QDir(getMetaData()["dataRoot"].toString() + QDir::separator() + getId());

    // Create the path if needed
    appDataPath.mkpath(appDataPath.absolutePath());

    // Set the config.json file
    QFile configsFile(appDataPath.absolutePath() + QDir::separator() + "config.json");
    configsFile.open(QFile::ReadWrite);

    QJsonDocument configsDocument = QJsonDocument().fromJson(configsFile.readAll());

    QJsonObject configs = configsDocument.object();

    QJsonValueRef ref = configs.find("Values").value();
    QJsonObject values = ref.toObject();

    values.insert(settingsID, newValue);

    ref = values;

    configsDocument.setObject(configs);

    if (configsFile.resize(0))
        configsFile.write(configsDocument.toJson());

    configsFile.close();
    setConfig(configs);
}

void fairwind::apps::web::Web::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}