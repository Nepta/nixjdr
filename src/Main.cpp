#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QLibraryInfo>
#include "MainWindow.h"
#include "ConnectionHelper.h"
#include "User.h"
#include "DataBase/DataBase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Translation
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale,
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    User *user = new User;
    ConnectionHelper connectionHelper(user);
    connectionHelper.exec();

    DataBase *database = new DataBase("jdrDB", user->getServerIpAddress());
    user->setDatabase(database);

    MainWindow mainWindow(user);
    mainWindow.show();

    return a.exec();
}
