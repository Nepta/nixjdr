#include <QString>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(bool role, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QMainWindow::showFullScreen();
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
    delete m_chatServer;
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

void MainWindow::on_msgField_returnPressed()
{
    m_chatClient->sendMessageToServer(ui->pseudoField->text(), ui->msgField->text());
}

void MainWindow::setupMJ() {
    setupChatServer();
    setupChatClient();
}

void MainWindow::setupPlayer() {
    setupChatClient();
}

void MainWindow::setupChatServer() {
    m_chatServer = new ChatServer;

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
    MainWindow::connect(m_chatClient, SIGNAL(clientConnected()),
                        this, SLOT(connectionSuccess()));
    MainWindow::connect(m_chatClient, SIGNAL(clientDisconnected()),
                        this, SLOT(disconnectionSuccess()));
}

void MainWindow::receivedMessage(const QString &msg) {
    ui->msgList->append(msg);
}

void MainWindow::connectionSuccess()
{
    ui->msgList->append(tr("<em>Connexion réussie !</em>"));
}

void MainWindow::disconnectionSuccess()
{
    ui->msgList->append(tr("<em>Déconnecté du serveur</em>"));
}
