#include <QApplication>
#include <QPushButton>


#include <QSettings>
#include "ui/MainWindow.hpp"
#include "core/FairWind.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    auto fairWind=fairwind::FairWind::getInstance();
    fairWind->setApplicationDirPath(QApplication::applicationDirPath().left(1));
    fairWind->loadExtensions();
    QSettings settings("fairwind.ini", QSettings::NativeFormat);
    QString configFile = settings.value("configFile", "fairwind.json").toString();
    settings.setValue("configFile",configFile);
    fairWind->loadConfig(configFile);

    QCoreApplication::setOrganizationName("uniparthenope");


    app.setWindowIcon(QIcon(QStringLiteral(":resources/images/fairwind_logo.png")));
    MainWindow w;

    auto fairWind1=fairwind::FairWind::getInstance();
    auto apps=fairWind1->getApps();

    return QApplication::exec();
}
