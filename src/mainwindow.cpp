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
    ui->tableArea->subWindowList().last()->setGeometry(0,0,470,90);
    ui->tableArea->subWindowList().last()->setMinimumSize(470,90);
    ui->tableArea->subWindowList().last()->setWindowTitle(tr("Dés"));
    connect(m_diceMenu, SIGNAL(rollDice(QString, bool)), this, SLOT(rollDice(QString, bool)));

    // Chat nicknames list
    m_NicknamesListModel = new QStringListModel;
    ui->nicknamesListView->setModel(m_NicknamesListModel);

    // Menu
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
    delete m_NicknamesListModel;
    delete m_diceMenu;
    delete m_chatServer;
    delete m_chatClient;
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
    MainWindow::connect(m_diceMenu, SIGNAL(sendMessageToUI(QString)),
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

void MainWindow::rollDice(QString dice, bool hidden){
    QString msg = QString("/roll %1").arg(dice);

    if (hidden) {
        msg += QString(" | %2").arg(m_chatClient->getUser()->getNickname());
    }

    sendMessageFromClientToServer(msg);
}

void MainWindow::updateNicknamesListView() {
    m_NicknamesListModel->setStringList(AbstractChatCmd::getUsersListClient()->keys());
}
