#include <QString>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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

        // TODO send string to sfml app

        ui->tableArea->addSubWindow(subWindow);
        subWindow->setGeometry(0, 0, ui->tableArea->width()/2, ui->tableArea->height()/2);
        subWindow->show();
    }
}
