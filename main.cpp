#include <QApplication>
#include <QPushButton>


#include <QSettings>
#include <QSplashScreen>
#include <core/SignalKWSClient.hpp>
#include <core/SignalKAPIClient.hpp>
#include "ui/MainWindow.hpp"
#include "sdk/include/FairWindSdk/FairWind.hpp"

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

    QSettings settings("fairwind.ini", QSettings::NativeFormat);
    QString configFile = settings.value("configFile", "fairwind.json").toString();
    settings.setValue("configFile",configFile);
    fairWind->loadConfig(configFile);

    splash.showMessage("Loading Organization Name",500, Qt::white);

    QCoreApplication::setOrganizationName("uniparthenope");


    app.setWindowIcon(QIcon(QStringLiteral(":resources/images/fairwind_logo.png")));
    MainWindow w;

    SignalKWSClient signalKWSClient(QUrl(QStringLiteral("ws://demo.signalk.org/signalk/v1/stream")), true);
    SignalKAPIClient signalKAPIClient(QUrl("http://demo.signalk.org/signalk/v1/api"));
    QString self = signalKAPIClient.getSelf();
    qDebug() << self;
    fairWind->getSignalKDocument()->setSelf(self);
    splash.finish(&w);
    return QApplication::exec();
}
