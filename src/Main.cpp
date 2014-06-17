#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QLibraryInfo>
#include <QStyleFactory>
#include "Database/Database.h"
#include "MainWindow.h"
#include "StyleSheet.h"
#include "ConnectionHelper.h"
#include "User.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // Translation
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale,
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    // Load QSS
    QFile File("resource/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(File.readAll());
    StyleSheet::setStyleSheet(stylesheet);

    User *user = new User;
    ConnectionHelper connectionHelper(user);
    connectionHelper.exec();

    Database::instantiate("jdrdb", user->getServerIpAddress(), 5432);

    MainWindow mainWindow(user);
    mainWindow.show();

    return a.exec();
}
