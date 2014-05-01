#include "Canvas.h"
#include <QApplication>
#include <QFrame>
#include <QPushButton>

#include <QMessageBox>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QLayout>
#include <QHBoxLayout>
#include <QGridLayout>

int main(int argc, char **argv)
{
    QApplication App(argc, argv);

    // On crée la fenêtre principale
    QWidget* MainFrame = new QWidget;
    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(400, 400);

    QPushButton bouton("Suwa~", MainFrame);


    MainFrame->show();

    //On crée une vue SFML dans la fenêtre principale
    Canvas* SFMLView = new Canvas(MainFrame, QPoint(30, 30), QSize(350, 350));
    SFMLView->show();

    return App.exec();
}
