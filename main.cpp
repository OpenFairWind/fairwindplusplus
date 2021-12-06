#include <QApplication>
#include <QPushButton>
#include <QSettings>
#include <QSplashScreen>

#include <FairWindSdk/FairWind.hpp>
#include <ui/settings/connections/Connections.hpp>
#include <ui/settings/applications/Applications.hpp>

#include <ui/settings/generic/Generic.hpp>

#include "ui/MainWindow.hpp"

/*
 * main
 * FairWind++ starting point
 */
int main(int argc, char *argv[]) {
    // Enable DPI scaling
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // Enable high DPI support
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    // Get the splash screen logo
    QPixmap pixmap(":/resources/images/icons/splash_logo.png");
    // Create a splash screen containing the logo
    QSplashScreen splash(pixmap);
    // Show the logo
    splash.show();

    // Get the FairWind singleton
    auto fairWind = fairwind::FairWind::getInstance();

    // Register settings pages inside the FairWind singleton
    fairWind->registerSettings(new fairwind::ui::settings::generic::Generic());
    fairWind->registerSettings(new fairwind::ui::settings::connections::Connections());
    fairWind->registerSettings(new fairwind::ui::settings::applications::Applications());

    splash.showMessage("Loading Applications ...", 500, Qt::white);

    // Set apps path
    fairWind->setApplicationDirPath(QApplication::applicationDirPath().left(1));
    // Load the apps inside the FairWind singleton itself
    fairWind->loadApps();

    splash.showMessage("Loading Settings ...", 500, Qt::white);

    // Load the configuration inside the FairWind singleton itself
    fairWind->loadConfig();

    splash.showMessage("Loading Organization Name", 500, Qt::white);

    // Set organisation name
    QCoreApplication::setOrganizationName("uniparthenope");

    // Set the window icon
    app.setWindowIcon(QIcon(QStringLiteral(":resources/images/fairwind_logo.png")));

    // Create a new MainWindow object
    fairwind::ui::MainWindow w;
    // Close the splash screen presenting the MainWindow UI
    splash.finish(&w);
    return QApplication::exec();
}
