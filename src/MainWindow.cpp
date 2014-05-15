#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QToolBox>
#include "CustomMdiArea.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "canvas/canvas.h"
#include "canvas/canvaseventhandler.h"

MainWindow::MainWindow(User *user, QWidget *parent) :
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
    m_User = user;
    if (m_User->getRole() == Role::ROLE_MJ) {
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
    delete m_User;
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
            Canvas* canvas = new Canvas(filename, 32);
    //        CanvasEventHandler* canvasEventHandler = new CanvasEventHandler();
            QSize sizeWindow;
            QSize sizeWidget;

            ui->tableArea->addSubWindow(canvas->getView());
            sizeWidget = canvas->getScene()->sceneRect().size().toSize();
            sizeWindow = ui->tableArea->subWindowList().last()->frameGeometry().size();
            ui->tableArea->subWindowList().last()->setMaximumSize(2*sizeWidget-sizeWindow);
            ui->tableArea->subWindowList().last()->show();

            connect(ui->tokenPage->getUi()->listToken,SIGNAL(itemClicked(QListWidgetItem*)), canvas->getCanvasEventHandler(), SLOT(setSpritePath(QListWidgetItem*)));

    }
}

void MainWindow::on_actionEditMap_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        }

}

void MainWindow::setupMJ() {
    ui->m_ChatWidget->setupChatServer();
    connect(m_diceMenu, SIGNAL(sendMessageToChatUi(QString)),
                        this, SIGNAL(sendMessageToChatUi(QString)));

    setupPlayer();
}

void MainWindow::setupPlayer() {
    ui->m_ChatWidget->setupChatClient(m_User);

    connect(this, SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString)));
}
