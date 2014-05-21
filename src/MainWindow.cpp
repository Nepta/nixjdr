#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QToolBox>

#include "canvas/CanvasScene.h"
#include "canvas/CanvasView.h"
#include "canvas/MapLayer.h"

#include "CustomMdiArea.h"
#include "MainWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(User *user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Sets Null pointer for later deletion if m_Server is not used
    m_Server = NULL;

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

    //showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_diceMenu;
    delete m_User;
    delete m_Server;
    delete m_Client;
}

void MainWindow::updateMenu() {
    QMdiSubWindow *subwindow  = ui->tableArea->activeSubWindow();
    if (subwindow != NULL) {
        /* TODO
         * QString classname = subwindow->metaObject()->className();
         * isMapSubwindow = (classname == QString("MapMdiSubwindow"));
         */

        bool isMapSubwindow = false;
        ui->actionEditMap->setEnabled(isMapSubwindow);
    }
}

void MainWindow::on_actionCreateMap_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        QListWidget *listWidget = ui->tokenPage->getUi()->listToken;

        // TODO Map class
        CanvasScene* scene = new CanvasScene(filename);

        // TODO should be able to choose the step value in a message box
        MapLayer *mapLayer = new MapLayer(listWidget->currentItem()->text(), 32);
        scene->addLayer(mapLayer);

        CanvasView* view = new CanvasView(scene);
        ui->tableArea->addSubWindow(view);
        view->show();

        connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                mapLayer, SLOT(setTokenPath(QListWidgetItem*)));

    }
}

void MainWindow::on_actionEditMap_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        // TODO
    }
}

void MainWindow::setupMJ() {
    m_Server = new Server;

    /* Connect sendMessageToChatUi from m_Server to m_ChatWidget in order to display system messages
     * during the initialization. &*/
    connect(m_Server, SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString))
    );

    // Server Initialization
    m_Server->init();

    // Initialize ChatWidget with the ChatServer
    ChatServer* chatServer = dynamic_cast<ChatServer*>(
                m_Server->getReceiver(TargetCode::CHAT_SERVER));
    ui->m_ChatWidget->setupChatServer(chatServer);

    setupPlayer();
}

void MainWindow::setupPlayer() {
    m_Client = new Client(m_User);

    connect(m_Client, SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString))
    );

    // Initialize ChatWidget with the ChatClient
    ChatClient* chatClient = dynamic_cast<ChatClient*>(
                m_Client->getReceiver(TargetCode::CHAT_CLIENT));
    ui->m_ChatWidget->setupChatClient(chatClient);

    /* The dice menu is able to send system messages to the Chat in order to display error messages
     * or warnings */
    connect(m_diceMenu, SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString))
    );
}
