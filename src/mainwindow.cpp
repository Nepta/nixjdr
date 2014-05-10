#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QToolBox>
#include <QPixmap>
#include <QGridLayout>

#include "QTSFML/MapMdiSubwindow.h"
#include "QTSFML/Map.h"
#include "CustomMdiArea.h"
#include "mainwindow.h"
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
    ui->tableArea->subWindowList().last()->setGeometry(0,0,275,100);
    connect(m_diceMenu, SIGNAL(rollDice(QString)), this, SLOT(rollDice(QString)));

    // Chat nicknames list
    m_NicknamesListModel = new QStringListModel;
    ui->nicknamesListView->setModel(m_NicknamesListModel);

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
    delete m_NicknamesListModel;
    delete m_diceMenu;
    delete m_chatServer;
    delete m_chatClient;
}

void MainWindow::on_actionModify_Background_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

	if (filename != NULL) {
        MapMdiSubwindow* SFMLWidget = new MapMdiSubwindow(filename);
        ui->tableArea->addSubWindow(SFMLWidget);
        SFMLWidget->show();

        connect(ui->tokenPage->getUi()->listToken, SIGNAL(itemClicked(QListWidgetItem*)),
                SFMLWidget->map(), SLOT(changeToken(QListWidgetItem*)));
	}
}

void MainWindow::on_msgField_returnPressed()
{
    if (!ui->msgField->text().isEmpty()) {
        sendMessageFromClientToServer(ui->msgField->text());
        ui->msgField->clear();
    }
}

void MainWindow::sendMessageFromClientToServer(QString message){
    m_chatClient->sendMessageToServer(message);
}

void MainWindow::setupMJ() {
    setupChatServer();
    setupChatClient();
}

void MainWindow::setupPlayer() {
    m_chatServer = NULL;
    setupChatClient();
}

void MainWindow::setupChatServer() {
    m_chatServer = new ChatServer;

    // connect needed before init to display system messages in the chat during
    // initialization
    MainWindow::connect(m_chatServer, SIGNAL(sendMessageToUI(QString)),
                        this, SLOT(receivedMessage(QString)));

    m_chatServer->init();
}

void MainWindow::setupChatClient() {
    m_chatClient = new ChatClient;

    // TEST
    m_chatClient->connection(QString("127.0.0.1"), 50885);
    // TEST

    MainWindow::connect(m_chatClient, SIGNAL(sendMessageToUI(QString)),
                        this, SLOT(receivedMessage(QString)));
    MainWindow::connect(m_chatClient->getChatCmds(), SIGNAL(cmdUpdateUserListView()),
                        this, SLOT(updateNicknamesListView()));
}

void MainWindow::receivedMessage(const QString &msg) {
    QString htmlMsg = QString("<div style=\" white-space: pre-wrap;\">%1</div>").arg(msg);
    ui->msgList->append(htmlMsg);
}

void MainWindow::rollDice(QString dice){
    sendMessageFromClientToServer(dice);
}

void MainWindow::updateNicknamesListView() {
    m_NicknamesListModel->setStringList(AbstractChatCmd::getUsersListClient()->keys());
}
