#include <QString>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Qt-sfml/QTSFML/Map.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionModify_Background_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "/home", "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        QMdiSubWindow* subWindow = new QMdiSubWindow();
        subWindow->setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint );

        ui->tableArea->addSubWindow(subWindow);
        subWindow->setGeometry(0, 0, ui->tableArea->width()/2, ui->tableArea->height()/2);
        subWindow->show();

        // On crée la fenêtre principale
        QWidget* SFMLWidget = new QMdiSubWindow();
        SFMLWidget->setWindowTitle("Qt SFML");
        SFMLWidget->resize(800, 600);
        SFMLWidget->show();

        //On crée une vue SFML dans la fenêtre principale
        QSFMLCanvas *map = new Map(SFMLWidget, QPoint(0, 0), QSize(800, 600));
        map->show();
    }
}
