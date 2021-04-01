#include <QApplication>
#include <QPushButton>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include "ui/MainWindow.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("uniparthenope");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral(":/images/fairwind_logo.png")));
    MainWindow w;

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif

    return QApplication::exec();
}
