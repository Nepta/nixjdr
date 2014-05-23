#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QToolBox>

#include "Canvas/CanvasScene.h"
#include "Canvas/CanvasView.h"
#include "Canvas/MapLayer.h"

#include "CustomMdiArea.h"
#include "ConnectionHelper.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(User *user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Sets Null pointer for later deletion if m_Server and/or m_Client are not used
    m_Server = NULL;
    m_Client = NULL;

    m_User = user;

    initTableTurnSplitter();
    initConnects();
    initRole();

    //showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_User;
    delete m_Server;
    delete m_Client;
}

void MainWindow::initTableTurnSplitter(){
    QList<int> sizes;
    sizes.push_back(1000);
    sizes.push_back(100);
    ui->tableTurnSplitter->setSizes(sizes);
}

void MainWindow::initConnects(){
    // Connect chat & dice menus
    connect(ui->turnWidget->getDiceWidget(), SIGNAL(rollDice(QString, bool)),
            ui->m_ChatWidget, SLOT(rollDice(QString, bool)));
    connect(ui->m_ChatWidget, SIGNAL(requestDice(QString&)),
            ui->turnWidget->getDiceWidget(), SLOT(requestRoll(QString&)));

    // Top menu
    connect(ui->tableArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
                 this, SLOT(updateMenu()));
}

void MainWindow::initRole(){

    if (m_User->getRole() == Role::ROLE_MJ) {
        setupMJ();
    } else {
        setupPlayer();
    }
}

void MainWindow::updateMenu() {
    QMdiSubWindow *subwindow  = ui->tableArea->activeSubWindow();
    if (subwindow != NULL) {
        bool isMapSubwindow = (subwindow->windowTitle() == tr("Carte"));

        ui->actionEditMap->setEnabled(isMapSubwindow);
    }
}

void MainWindow::createMap(QString filename) {
    QListWidget *tokenList = ui->tokenPage->getUi()->m_tokenList;

    // TODO should be able to choose the step value in a message box
    Map *map = new Map(filename, tokenList->currentItem()->text(), 32);

    QMdiSubWindow *subwindow = ui->tableArea->addSubWindow(map);
    subwindow->show();
    subwindow->move(0, 0);

    connect(tokenList, SIGNAL(currentItemChanged(QListWidgetItem*,  QListWidgetItem *)),
            map->getMapLayer(), SLOT(setSpritePath(QListWidgetItem*)));
}

void MainWindow::on_actionCreateMap_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        createMap(filename);
    }
}

void MainWindow::on_actionEditMap_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        delete ui->tableArea->activeSubWindow();
        createMap(filename);
    }
}

void MainWindow::on_actionConnection_triggered(){
    User* tmpUser = new User();
    ConnectionHelper connectionHelper(tmpUser);
    connectionHelper.exec();
    MainWindow* mainWindow = new MainWindow(tmpUser);
    mainWindow->show();
    delete m_User;
    delete m_Server;
    delete m_Client;
    this->destroy();
}

void MainWindow::setupMJ() {
    m_Server = new Server;

    /* Connect sendMessageToChatUi from m_Server to m_ChatWidget in order to display system messages
     * during the initialization. */
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
    connect(ui->turnWidget->getDiceWidget(), SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString))
    );
}
