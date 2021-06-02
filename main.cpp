#include <QApplication>
#include <QPushButton>


#include <QSettings>
#include <QSplashScreen>
#include <core/SignalKWSClient.hpp>
#include <core/SignalKAPIClient.hpp>
#include "ui/MainWindow.hpp"
#include <FairWindSdk/FairWind.hpp>
#include <FairWindSdk/SignalKLayer.hpp>
#include <sdk/include/FairWindSdk/FairWindOSMLayer.hpp>
#include <sdk/include/FairWindSdk/FairWindTiledLayer.hpp>
#include <sdk/include/FairWindSdk/display/DisplaySingleText.hpp>
#include <sdk/include/FairWindSdk/display/DisplayDoubleText.hpp>
#include <sdk/include/FairWindSdk/display/DisplayChart.hpp>
#include <sdk/include/FairWindSdk/display/DisplayGauge.hpp>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    QPixmap pixmap(":/resources/images/icons/splash_logo.png");
    QSplashScreen splash(pixmap);
    splash.show();

    auto fairWind=fairwind::FairWind::getInstance();

    splash.showMessage("Loading Applications ...",500, Qt::white);

    fairWind->setApplicationDirPath(QApplication::applicationDirPath().left(1));
    fairWind->loadApps();

    splash.showMessage("Loading Settings ...",500, Qt::white);


    fairWind->loadConfig();

    splash.showMessage("Loading Organization Name",500, Qt::white);

    QCoreApplication::setOrganizationName("uniparthenope");


    app.setWindowIcon(QIcon(QStringLiteral(":resources/images/fairwind_logo.png")));



    SignalKAPIClient signalKAPIClient(QUrl("http://demo.signalk.org/signalk/v1/api"));
    QString self = signalKAPIClient.getSelf();
    qDebug() << "self: " << self;

    //fairWind->getSignalKDocument()->setSelf(self);
    QJsonObject allSignalK=signalKAPIClient.getAll();
    fairWind->getSignalKDocument()->setRoot(allSignalK);
    SignalKWSClient signalKWSClient(QUrl(QStringLiteral("ws://demo.signalk.org/signalk/v1/stream")), true);


    MainWindow w;
    splash.finish(&w);
    return QApplication::exec();
}
