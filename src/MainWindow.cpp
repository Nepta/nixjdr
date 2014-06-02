#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QToolBox>

#include "Database/Repository/RepositoryManager.h"

#include "Canvas/Network/MapClient.h"
#include "Canvas/Network/MapServer.h"
#include "Canvas/Layers/MapLayer.h"
#include "Canvas/CanvasScene.h"
#include "Canvas/CanvasView.h"
#include "Canvas/ImageWidget.h"

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

    initDBComponents();
    initTableTurnSplitter();
    initConnects();
    initRole();

    //showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Server;
    delete m_Client;
}

/**
 * @brief MainWindow::initDBComponents Initializes all the objects from classes inheriting DBComponent
 * with the application Database.
 */
void MainWindow::initDBComponents() {
    ui->tokenPage->initTokenMenu(db_);
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

    TokenItem *currentTokenItem = dynamic_cast<TokenItem*>(tokenList->currentItem());
    // TODO should be able to choose the step value in a message box
    Map *map = new Map(filename, currentTokenItem, 32);
    map->setDatabase(db_);

    // Add Map to the database
    RepositoryManager::s_MapRepository.insertMap(map, db_);

    // Initialize Map with the MapServer
    if (m_Server != NULL) {
        MapServer* mapServer = dynamic_cast<MapServer*>(
                    m_Server->getReceiver(TargetCode::MAP_SERVER));
        map->setupServerReceiver(mapServer);
    }

    // Initialize Map with the MapClient
    MapClient* mapClient = dynamic_cast<MapClient*>(
                m_Client->getReceiver(TargetCode::MAP_CLIENT));
    mapClient->addMapToList(map);
    map->setupClientReceiver(mapClient);

    QMdiSubWindow *subwindow = ui->tableArea->addSubWindow(map);
    subwindow->show();
    subwindow->move(0, 0);

    connect(tokenList, SIGNAL(currentItemChanged(QListWidgetItem*,  QListWidgetItem *)),
            map->getMapLayer(), SLOT(setTokenItem(QListWidgetItem*)));
}

void MainWindow::on_actionCreateMap_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        createMap(filename);
    }
}

void MainWindow::on_actionCreateImage_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if (filename != NULL) {
        createImage(filename);
    }
}

void MainWindow::createImage(QString filename) {
    // TODO should be able to choose the step value in a message box
    ImageWidget *image = new ImageWidget(filename);
    QMdiSubWindow *subwindow = ui->tableArea->addSubWindow(image);
    subwindow->show();
    subwindow->move(0, 0);
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
    ui->m_ChatWidget->setupServerReceiver(chatServer);

    setupPlayer();
}

void MainWindow::setupPlayer() {
    TokenList *tokenList = ui->tokenPage->getUi()->m_tokenList;
    m_Client = new Client(m_User, db_, tokenList);

    connect(m_Client, SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString))
    );

    // Initialize ChatWidget with the ChatClient
    ChatClient* chatClient = dynamic_cast<ChatClient*>(
                m_Client->getReceiver(TargetCode::CHAT_CLIENT));
    ui->m_ChatWidget->setupClientReceiver(chatClient);

    /* The dice menu is able to send system messages to the Chat in order to display error messages
     * or warnings */
    connect(ui->turnWidget->getDiceWidget(), SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString))
    );
}

void MainWindow::on_collapseButtonRightMenu_clicked(bool checked)
{
    int min = ui->collapseButtonRightMenu->minimumWidth();
    int max = ui->actionMenu->minimumWidth() + ui->collapseButtonRightMenu->minimumWidth();
    collapseMenu(checked, ui->rightMenuWidget, ui->rightMenuSplitter, min, max);
}

void MainWindow::on_collapseButtonTurnMenu_clicked(bool checked)
{
    int min = ui->collapseButtonTurnMenu->minimumHeight();
    int max = ui->turnWidget->minimumHeight() + ui->collapseButtonTurnMenu->minimumHeight();
    collapseMenu(checked, ui->turnWidget, ui->tableTurnSplitter, min, max);
}

void MainWindow::collapseMenu(bool checked, QWidget *widget, QSplitter *splitter, int min, int max){
    QList<int> sizes = splitter->sizes();
    widget->setVisible(checked);
    if(checked){
        sizes[1] = max;
    }
    else{
        sizes[1] = min;
    }
    splitter->setSizes(sizes);
}
