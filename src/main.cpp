#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QLibraryInfo>
#include "startdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Translation
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale,
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    bool role;
    StartDialog startDialog(NULL);
    role = startDialog.resultExec();

    MainWindow w(role);
    w.show();

    return a.exec();
}
