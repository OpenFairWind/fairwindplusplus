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

    // Initialize the QT managed settings
    QSettings settings("fairwind.ini", QSettings::NativeFormat);

    // Is a virtual keyboard needed?
    bool useVirtualKeyboard = settings.value("useVirtualKeyboard",false).toBool();

    // Check if a virtual keyboard is needed
    if (useVirtualKeyboard) {

        // Activate the on screen virtual keyboard
        qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    }

    // Set dpi scaling attributes
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Create the QT Application
    QApplication app(argc, argv);

    // Get the splash screen bitmap
    QPixmap pixmap(":/resources/images/icons/splash_logo.png");

    // Create the splash screen
    QSplashScreen splash(pixmap);

    // Show the splash screen
    splash.show();

    // Get the FairWind singleton instance
    auto fairWind=fairwind::FairWind::getInstance();

    // Register settings pages
    fairWind->registerSettings(new fairwind::ui::settings::generic::Generic());
    fairWind->registerSettings(new fairwind::ui::settings::connections::Connections());
    fairWind->registerSettings(new fairwind::ui::settings::applications::Applications());

    // Show a message on the splash screen
    splash.showMessage("Loading Applications ...",500, Qt::white);

    // Set the application path
    fairWind->setApplicationDirPath(QApplication::applicationDirPath().left(1));

    // Load the applications as QT plugins
    fairWind->loadApps();

    // Show a message on the splash screen
    splash.showMessage("Loading Settings ...",500, Qt::white);

    // Load configuration
    fairWind->loadConfig();

    // Show a message on the splash screen
    splash.showMessage("Loading Organization Name",500, Qt::white);

    // Set the organization name
    QCoreApplication::setOrganizationName("uniparthenope");

    // Set the application window icon
    app.setWindowIcon(QIcon(QStringLiteral(":resources/images/fairwind_logo.png")));

    // Create the main window
    fairwind::ui::MainWindow w;

    // Close the splash screen and open the main window
    splash.finish(&w);

    // Execute the application lifecycle
    return QApplication::exec();
}
