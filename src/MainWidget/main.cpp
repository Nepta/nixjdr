#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QLibraryInfo>
#include "startdialog.h"

// TODO refacto
void startChoiceDialog() {
    QMessageBox startChoice(QMessageBox::Question, "Choix rôle",
                            "Comment voulez-vous utiliser l'application?",
                            QMessageBox::Yes | QMessageBox::No, NULL);
    startChoice.setWindowModality(Qt::WindowModal);

    startChoice.setButtonText(QMessageBox::Yes, "MJ");
    startChoice.setButtonText(QMessageBox::No, "Joueur");

    if (startChoice.exec() == QMessageBox::No) {
        // TODO
    } else {
        // TODO
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Translation
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale,
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    StartDialog startDialog(NULL);
    startDialog.resultExec();

    MainWindow w;
    w.show();

    return a.exec();
}
