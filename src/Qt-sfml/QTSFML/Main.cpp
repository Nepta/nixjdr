#include "Canvas.h"
#include "Map.h"

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

int main(int argc, char **argv){
	QApplication App(argc, argv);

	// On crée la fenêtre principale
	QWidget* MainFrame = new QWidget;
	MainFrame->setWindowTitle("Qt SFML");
	MainFrame->resize(800, 600);

//    QPushButton bouton("Suwa~", MainFrame);


	MainFrame->show();

	//On crée une vue SFML dans la fenêtre principale
	QSFMLCanvas *map;
	if(argc > 1){
		map = new Canvas(MainFrame,QPoint(0,0), QSize(800, 600));
	}else{
		map = new Map(MainFrame, QPoint(0, 0), QSize(800, 600));
	}
	map->show();

 return App.exec();
}
