#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QToolBox>
#include "QTSFML/MapMdiSubwindow.h"
#include "QTSFML/Map.h"
#include "CustomMdiArea.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(bool role, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Dice menu
    m_diceMenu = new DiceMenu();
    ui->tableArea->addSubWindow(m_diceMenu, Qt::CustomizeWindowHint |
                                Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

    ui->tableArea->subWindowList().last()->setGeometry(0,0,470,90);
    ui->tableArea->subWindowList().last()->setMinimumSize(ui->tableArea->size());
    ui->tableArea->subWindowList().last()->setWindowTitle(tr("Dés"));
    connect(m_diceMenu, SIGNAL(rollDice(QString, bool)),
            ui->m_ChatWidget, SLOT(rollDice(QString, bool)));

    // Top menu
    connect(ui->tableArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
                 this, SLOT(updateMenu()));

    // Setup role
    m_role = role;
    if (m_role == ROLE_MJ) {
        setupMJ();
    } else {
        setupPlayer();
    }

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_diceMenu;
}

void MainWindow::updateMenu() {
    QMdiSubWindow *subwindow  = ui->tableArea->activeSubWindow();
    if (subwindow) {
        QString classname = subwindow->metaObject()->className();

        bool isMapMdiSubWindow = (classname == QString("MapMdiSubwindow"));
        ui->actionEditMap->setEnabled(isMapMdiSubWindow);
    }
}

void MainWindow::on_actionCreateMap_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

	if (filename != NULL) {
        MapMdiSubwindow* SFMLWidget = new MapMdiSubwindow();
        ui->tableArea->addSubWindow(SFMLWidget);
        SFMLWidget->editMapBackgroud(filename, true);
        SFMLWidget->show();

        connect(ui->tokenPage->getUi()->listToken, SIGNAL(itemClicked(QListWidgetItem*)),
                SFMLWidget->map(), SLOT(changeToken(QListWidgetItem*)));
	}
}

void MainWindow::on_actionEditMap_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        MapMdiSubwindow *subwindow = dynamic_cast<MapMdiSubwindow*>(ui->tableArea->activeSubWindow());
        subwindow->editMapBackgroud(filename, false);

        connect(ui->tokenPage->getUi()->listToken, SIGNAL(itemClicked(QListWidgetItem*)),
                subwindow->map(), SLOT(changeToken(QListWidgetItem*)));
    }

}

void MainWindow::setupMJ() {
    ui->m_ChatWidget->setupChatServer();
    connect(m_diceMenu, SIGNAL(sendMessageToChatUi(QString)),
                        this, SIGNAL(sendMessageToChatUi(QString)));

    ui->m_ChatWidget->setupChatClient();
}

void MainWindow::setupPlayer() {
    ui->m_ChatWidget->setupChatClient();

    connect(this, SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString)));
}
