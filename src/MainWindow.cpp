#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QToolBox>

#include "Chat/Commands/CmdNickname.h"

#include "Database/Repository/RepositoryManager.h"

#include "Token/Network/TokenMenuClient.h"
#include "Token/Network/TokenMenuServer.h"

#include "TurnMenu/Network/TurnMenuClient.h"
#include "TurnMenu/Network/TurnMenuServer.h"

#include "Log/LogClient.h"
#include "Log/LogServer.h"

#include "Canvas/OpenMapWidget.h"
#include "Canvas/Network/MapClient.h"
#include "Canvas/Network/MapServer.h"
#include "Canvas/Layers/MapLayer.h"
#include "Canvas/CanvasScene.h"
#include "Canvas/CanvasView.h"

#include "StyleSheet.h"
#include "CustomMdiArea.h"
#include "ConnectionHelper.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(User *user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet(StyleSheet::s_StyleSheet);

    // Sets Null pointer for later deletion if m_Server and/or m_Client are not used
    m_Server = NULL;
    m_Client = NULL;

    m_User = user;

    initConnects();
    initRole();
	initLogger();
    m_NotificationStacker.setParent(this);

    //showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Server;
    delete m_Client;
}

void MainWindow::initLogger(){
	//WARNING deficient by design ...
	QHash<QString, User*> *userList = m_Server->getUserList();
	LogClient *logClient = new LogClient(m_User, nullptr, *ui->m_LogGui);
	LogServer *logServer = new LogServer(userList);
	if(m_Server){
		m_Server->insert(TargetCode::LOGGER_SERVER, logServer);
	}
	m_Client->insert(TargetCode::LOGGER_CLIENT, logClient);
}

void MainWindow::initConnects() {
    // Top menu
    connect(ui->tableArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
                 this, SLOT(updateMenu()));
}

void MainWindow::initRole(){

    if (m_User->getRole() == Role::ROLE_MJ) {
        setupMJ();
        m_IsMj = true;
    } else {
        setupPlayer();
        m_IsMj = false;
    }
}

/**
 * @brief MainWindow::updateMenu Update the top menu available functions.
 */
void MainWindow::updateMenu() {
    // TODO update menu
}

/**
 * @brief MainWindow::openMap Initialize and opens the given map.
 * @param map
 * @param notify Notifies all the clients that a new map has been opened if true.
 */
void MainWindow::openMap(Map *map, bool notify) {
    QListWidget *tokenList = ui->tokenPage->getUi()->m_tokenList;

    // Initialize Map with the MapServer
    if (m_Server != NULL) {
        Receiver *mapServerReceiver = m_Client->getReceiver(TargetCode::MAP_SERVER);
        MapServer *mapServer = dynamic_cast<MapServer*>(mapServerReceiver);
        map->setSenderServer(mapServer);
    }

    // Initialize Map with the MapClient
    Receiver *mapClientReceiver = m_Client->getReceiver(TargetCode::MAP_CLIENT);
    MapClient *mapClient = dynamic_cast<MapClient*>(mapClientReceiver);
    mapClient->addMapToList(map);
    map->setSenderClient(mapClient);

    QMdiSubWindow *subwindow = ui->tableArea->addSubWindow(map);
    subwindow->show();
    subwindow->move(0, 0);

    connect(tokenList, SIGNAL(currentItemChanged(QListWidgetItem*,  QListWidgetItem *)),
            map->getMapLayer(), SLOT(setTokenItem(QListWidgetItem*))
    );

    if (notify) {
        // Notifies all the clients that a new map has been opened
        Receiver *mapClientReceiver = m_Client->getReceiver(TargetCode::MAP_CLIENT);
        MapClient *mapClient = dynamic_cast<MapClient*>(mapClientReceiver);
        QString msg = QString("%1").arg(map->id());
        mapClient->sendMessageToServer(msg, (quint16) MapCodes::OPEN_MAP);
    }

    m_NotificationStacker.pushNotification("Une carte a été ouverte");

    // Connect to the LogClient
    TargetCode logClientCode(TargetCode::LOGGER_CLIENT);
    Receiver *logClientReceiver = m_Client->getReceiver(logClientCode);
    LogClient *logClient = dynamic_cast<LogClient*>(logClientReceiver);
    map->connectToLogger(logClient);
}

void MainWindow::createMap(QString mapName, int mapStep, bool isMap) {
    QListWidget *tokenList = ui->tokenPage->getUi()->m_tokenList;
    TokenItem *currentTokenItem = dynamic_cast<TokenItem*>(tokenList->currentItem());

    Map *map = new Map(isMap, mapName, m_FilePath , currentTokenItem, mapStep, m_IsMj);

    // Add Map to the database
    RepositoryManager::s_MapRepository.insertMap(map);

    // Initialize and open map
    openMap(map, true);
}

void MainWindow::on_actionCreateMap_triggered(){
    m_FilePath = "";
    m_FilePath = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if(m_FilePath != ""){
        MapCreationWidget mapCreationWidget(false);
        connect(&mapCreationWidget, SIGNAL(createMap(QString, int, bool)),
                this, SLOT(createMap(QString, int, bool)));
        mapCreationWidget.exec();
    }
}

void MainWindow::on_actionOpenMap_triggered() {
    int mapId = 0;
    OpenMapWidget openMapWidget(&mapId);
    openMapWidget.exec();

    // If the map has already been opened, don't open it again
    Receiver *mapClientReceiver = m_Client->getReceiver(TargetCode::MAP_CLIENT);
    MapClient *mapClient = dynamic_cast<MapClient*>(mapClientReceiver);
    if (mapClient->containsMap(mapId)) {
        return;
    }

    if (mapId != 0) {
        TokenList *tokenList = ui->tokenPage->getUi()->m_tokenList;
        Map *map = RepositoryManager::s_MapRepository.findMapById(mapId, tokenList);
        map->getMapLayer()->setTokenItem(tokenList->currentItem());

        openMap(map, true);
    }
}

void MainWindow::on_actionCreateImage_triggered(){
    m_FilePath = "";
    m_FilePath = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

    if(m_FilePath != ""){
        MapCreationWidget mapCreationWidget(true);
        connect(&mapCreationWidget, SIGNAL(createMap(QString, int, bool)),
                this, SLOT(createMap(QString, int, bool)));
        mapCreationWidget.exec();
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
    m_Server = new SwitchServer();

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
    ui->m_ChatWidget->setSenderServer(chatServer);

    // Initialize TokenMenu with the TokenMenuServer
    Receiver *tokenMenuServerReceiver = m_Server->getReceiver(TargetCode::TOKEN_MENU_SERVER);
    TokenMenuServer *tokenMenuServer = dynamic_cast<TokenMenuServer*>(tokenMenuServerReceiver);
    ui->tokenPage->setSenderServer(tokenMenuServer);

    // Initialize TurnMenu with the TurnMenuServer
    Receiver *turnMenuServerReceiver = m_Server->getReceiver(TargetCode::TURN_MENU_SERVER);
    TurnMenuClient *turnMenuServer = dynamic_cast<TurnMenuClient*>(turnMenuServerReceiver);
    ui->turnWidget->setSenderClient(turnMenuServer);

    setupPlayer();

    connect(dynamic_cast<CmdNickname *>(chatServer->getCommands()->getUserCommand(ChatCodes::USERCMD_NICK)),
            SIGNAL(addPlayerToInterface(QString)),
            this,
            SLOT(addPlayerToInterface(QString)));
}

void MainWindow::addPlayerToInterface(QString playerNickname){
    ui->turnWidget->getTurnList()->addTurn(playerNickname);
    ui->tokenPage->addCustomToken(playerNickname);
}


void MainWindow::setupPlayer() {

    TokenMenu *tokenMenu = ui->tokenPage;
    TurnMenu *turnMenu = ui->turnWidget;
    m_Client = new SwitchClient(m_User, tokenMenu, turnMenu);

    connect(m_Client, SIGNAL(sendMessageToChatUi(QString)),
            ui->m_ChatWidget, SLOT(receivedMessage(QString))
    );

    // Initialize ChatWidget with the ChatClient
    ChatClient* chatClient = dynamic_cast<ChatClient*>(
                m_Client->getReceiver(TargetCode::CHAT_CLIENT));
    ui->m_ChatWidget->setSenderClient(chatClient);

    // Initialize MapClient connect
    Receiver *mapClientReceiver = m_Client->getReceiver(TargetCode::MAP_CLIENT);
    MapClient *mapClient = dynamic_cast<MapClient*>(mapClientReceiver);
    connect(mapClient, SIGNAL(openMap(Map*)), this, SLOT(openMap(Map*)));

    // Initialize TokenMenu with the TokenMenuClient
    Receiver *tokenMenuClientReceiver = m_Client->getReceiver(TargetCode::TOKEN_MENU_CLIENT);
    TokenMenuClient *tokenMenuClient = dynamic_cast<TokenMenuClient*>(tokenMenuClientReceiver);
    ui->tokenPage->setSenderClient(tokenMenuClient);

    // Initialize TurnMenu with the TurnMenuClient
    Receiver *turnMenuClientReceiver = m_Client->getReceiver(TargetCode::TURN_MENU_CLIENT);
    TurnMenuClient *turnMenuClient = dynamic_cast<TurnMenuClient*>(turnMenuClientReceiver);
    ui->turnWidget->setSenderClient(turnMenuClient);
}

void MainWindow::on_collapseButtonRightMenu_clicked(bool checked)
{
    int min = ui->collapseButtonRightMenu->minimumWidth();
    int max = ui->actionMenu->minimumWidth() + ui->collapseButtonRightMenu->minimumWidth();
    collapseMenu(checked, ui->rightMenuWidget, ui->rightMenuSplitter, min, max);
}

void MainWindow::on_collapseButtonTurnMenu_clicked() {
    bool isVisible = ui->turnWidget->isVisible();
    ui->turnWidget->setVisible(!isVisible);
}

void MainWindow::collapseMenu(bool checked, QWidget *widget, QSplitter *splitter, int min, int max) {
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
