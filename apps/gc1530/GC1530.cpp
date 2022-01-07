//
// Created by __author__ on 16/07/2021.
//

#include <FairWindSdk/FairWind.hpp>
#include "GC1530.hpp"

#include "WebView.hpp"

#include <QWebEngineSettings>
#include <QWebEngineProfile>

/*
 * Returns the application icon
 */
QImage it::gov::guardiacostiera::gc1530::GC1530::getIcon() const {
    return QImage(":/resources/images/icons/gc1530_icon.png");
}

/*
 * Called by the FairWind framework when the app is invoked for the first time
 */
QWidget *it::gov::guardiacostiera::gc1530::GC1530::onStart(QMainWindow *mainWindow, QMap<QString, QVariant> args) {

    m_widget=new QWidget();
    ui=new Ui::GC1530();
    ui->setupUi(m_widget);

    auto fairwind=::fairwind::FairWind::getInstance();
    auto config = getConfig();

    m_webView = new WebView(m_widget);
    m_webView->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    auto *widgetWebApp_Buttons = new QWidget(m_widget);

    auto *pushButton_Home = new QPushButton(widgetWebApp_Buttons);
    pushButton_Home->setText("Home");

    connect(pushButton_Home, &QPushButton::clicked, this, &::it::gov::guardiacostiera::gc1530::GC1530::toolButton_home_clicked);

    auto *pushButton_Prev = new QPushButton(widgetWebApp_Buttons);
    pushButton_Prev->setText("<");

    auto *pushButton_Next = new QPushButton(widgetWebApp_Buttons);
    pushButton_Next->setText(">");

    auto *hBoxLayout = new QHBoxLayout();
    m_widget->setLayout(hBoxLayout);
    hBoxLayout->addWidget(m_webView);
    hBoxLayout->addWidget(widgetWebApp_Buttons);

    auto *vBoxLayout = new QVBoxLayout();
    vBoxLayout->setAlignment(Qt::AlignTop);
    vBoxLayout->addWidget(pushButton_Home);
    vBoxLayout->addWidget(pushButton_Prev);
    vBoxLayout->addWidget(pushButton_Next);
    widgetWebApp_Buttons->setLayout(vBoxLayout);

    m_webView->load(QUrl(m_url));

    return m_widget;
}



QString it::gov::guardiacostiera::gc1530::GC1530::getId() const {
    return AppBase::getId();
}

QString it::gov::guardiacostiera::gc1530::GC1530::getName() const {
    return AppBase::getName();
}

QString it::gov::guardiacostiera::gc1530::GC1530::getDesc() const {
    return AppBase::getDesc();
}

QString it::gov::guardiacostiera::gc1530::GC1530::getVersion() const {
    return fairwind::AppBase::getVersion();
}

QString it::gov::guardiacostiera::gc1530::GC1530::getVendor() const {
    return fairwind::AppBase::getVendor();
}

QString it::gov::guardiacostiera::gc1530::GC1530::getCopyright() const {
    return fairwind::AppBase::getCopyright();
}

QString it::gov::guardiacostiera::gc1530::GC1530::getLicense() const {
    return fairwind::AppBase::getLicense();
}


void it::gov::guardiacostiera::gc1530::GC1530::onCreate(QJsonObject *metaData) {
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif
    m_profile = QWebEngineProfile::defaultProfile();
    AppBase::onCreate(metaData);

    auto fairWind = fairwind::FairWind::getInstance();
    //fairWind->registerLayer(new NavionicsLayer());

    m_url = "https://www.guardiacostiera.gov.it";
}

void it::gov::guardiacostiera::gc1530::GC1530::onResume() {
    AppBase::onResume();
}

void it::gov::guardiacostiera::gc1530::GC1530::onPause() {
    AppBase::onPause();
}

void it::gov::guardiacostiera::gc1530::GC1530::onStop() {
    AppBase::onStop();
}

void it::gov::guardiacostiera::gc1530::GC1530::onDestroy() {
    AppBase::onDestroy();
}

QJsonObject it::gov::guardiacostiera::gc1530::GC1530::getConfig() {
    return AppBase::getConfig();
}

QJsonObject it::gov::guardiacostiera::gc1530::GC1530::getMetaData() {
    return AppBase::getMetaData();
}

void it::gov::guardiacostiera::gc1530::GC1530::toolButton_home_clicked() {
    m_webView->load(QUrl(m_url));
}

void it::gov::guardiacostiera::gc1530::GC1530::updateSettings(QString settingsID, QString newValue) {
    AppBase::updateSettings(settingsID, newValue);
}

void it::gov::guardiacostiera::gc1530::GC1530::setConfig(QJsonObject config) {
    AppBase::setConfig(config);
}

QJsonObject it::gov::guardiacostiera::gc1530::GC1530::getSettings() {
    return AppBase::getSettings();
}