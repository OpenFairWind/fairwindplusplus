#include <QApplication>
#include <QPushButton>


#include <QSettings>
#include <QSplashScreen>

#include "ui/MainWindow.hpp"
#include <FairWindSdk/FairWind.hpp>
#include <ui/settings/generic/Generic.hpp>
#include <ui/settings/connections/Connections.hpp>
#include <ui/settings/applications/Applications.hpp>

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    QPixmap pixmap(":/resources/images/icons/splash_logo.png");
    QSplashScreen splash(pixmap);
    splash.show();

    auto fairWind=fairwind::FairWind::getInstance();

    // Register settings pages
    fairWind->registerSettings(new fairwind::ui::settings::generic::Generic());
    fairWind->registerSettings(new fairwind::ui::settings::connections::Connections());
    fairWind->registerSettings(new fairwind::ui::settings::applications::Applications());

    splash.showMessage("Loading Applications ...",500, Qt::white);

    fairWind->setApplicationDirPath(QApplication::applicationDirPath().left(1));
    fairWind->loadApps();

    splash.showMessage("Loading Settings ...",500, Qt::white);


    fairWind->loadConfig();

    splash.showMessage("Loading Organization Name",500, Qt::white);

    QCoreApplication::setOrganizationName("uniparthenope");

    app.setWindowIcon(QIcon(QStringLiteral(":resources/images/fairwind_logo.png")));



    fairwind::ui::MainWindow w;
    splash.finish(&w);
    return QApplication::exec();
}
