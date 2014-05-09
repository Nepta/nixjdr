#include <QString>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QApplication>
#include <QDesktopWidget>
#include "QTSFML/QTSFMLMdiSubwindow.h"
#include "QTSFML/Map.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(bool role, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_NicknamesListModel = new QStringListModel;
    ui->nicknamesListView->setModel(m_NicknamesListModel);

    m_role = role;
    if (m_role == ROLE_MJ) {
        setupMJ();
    } else {
        setupPlayer();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_NicknamesListModel;
    delete m_chatServer;
    delete m_chatClient;
}

void MainWindow::on_actionModify_Background_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                    "Images (*.png *.xpm *.jpg)");

	if (filename != NULL) {
		// On crée la fenêtre principale
        int height = 600;
		int width = 800;
        int margin = 24;

        QTSFMLMdiSubwindow* SFMLWidget = new QTSFMLMdiSubwindow(filename, height, width, margin);
		ui->tableArea->addSubWindow(SFMLWidget);
        SFMLWidget->show();
	}
}

void MainWindow::on_msgField_returnPressed()
{
    if (!ui->msgField->text().isEmpty()) {
        m_chatClient->sendMessageToServer(ui->msgField->text());
        ui->msgField->clear();
    }
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
    ui->msgList->append(msg);
}

void MainWindow::updateNicknamesListView() {
    m_NicknamesListModel->setStringList(AbstractChatCmd::getUsersListClient()->keys());
}
