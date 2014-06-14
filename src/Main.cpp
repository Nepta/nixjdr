#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QLibraryInfo>
#include "QStyleFactory"
#include "MainWindow.h"
#include "ConnectionHelper.h"
#include "User.h"
#include "Database/Database.h"

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

    User *user = new User;
    ConnectionHelper connectionHelper(user);
    connectionHelper.exec();

    Database::instantiate("jdrdb", "127.0.0.1", 5432);

    MainWindow mainWindow(user);
    mainWindow.show();

    return a.exec();
}
