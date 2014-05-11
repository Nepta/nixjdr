#include "ChatWidget.h"
#include "ui_ChatWidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);

    // Set m_ChatServer to NULL pointer in order to allow deletion later if it is not used
    m_ChatServer = NULL;

    // Chat nicknames list
    m_NicknamesListModel = new QStringListModel;
    ui->nicknamesListView->setModel(m_NicknamesListModel);
}

ChatWidget::~ChatWidget()
{
    delete ui;
    delete m_NicknamesListModel;
    delete m_ChatServer;
    delete m_ChatClient;
}

void ChatWidget::on_msgField_returnPressed()
{
    if (!ui->msgField->text().isEmpty()) {
        m_ChatClient->sendMessageToServer(ui->msgField->text());
        ui->msgField->clear();
    }
}

void ChatWidget::setupChatServer() {
    m_ChatServer = new ChatServer;

    // connect needed before init to display system messages in the chat during initialization
    connect(m_ChatServer, SIGNAL(sendMessageToChatUi(QString)),
                        this, SLOT(receivedMessage(QString)));
    m_ChatServer->init();
}

void ChatWidget::setupChatClient() {
    // TEST
    m_ChatClient = new ChatClient(QString("127.0.0.1"), 50885);
    // TEST

    connect(m_ChatClient, SIGNAL(sendMessageToChatUi(QString)),
                        this, SLOT(receivedMessage(QString)));
    connect(m_ChatClient->getCommands(), SIGNAL(cmdUpdateUserListView()),
                        this, SLOT(updateNicknamesListView()));
}

void ChatWidget::receivedMessage(const QString &msg) {
    QString htmlMsg = QString("<div style=\" white-space: pre-wrap;\">%1</div>").arg(msg);
    ui->msgList->append(htmlMsg);
}

void ChatWidget::updateNicknamesListView() {
    m_NicknamesListModel->setStringList(AbstractCmd::getUsersListClient()->keys());
}

void ChatWidget::rollDice(QString dice, bool hidden){
    QString msg = QString("/roll %1").arg(dice);

    if (hidden) {
        msg += QString(" | %2").arg(m_ChatClient->getUser()->getNickname());
    }

     m_ChatClient->sendMessageToServer(msg);
}
