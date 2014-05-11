#include "ChatWidget.h"
#include "ui_ChatWidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);

    // Set m_chatServer to NULL pointer in order to allow deletion later if it is not used
    m_chatServer = NULL;

    // Chat nicknames list
    m_NicknamesListModel = new QStringListModel;
    ui->nicknamesListView->setModel(m_NicknamesListModel);
}

ChatWidget::~ChatWidget()
{
    delete ui;
    delete m_NicknamesListModel;
    delete m_chatServer;
    delete m_chatClient;
}

void ChatWidget::on_msgField_returnPressed()
{
    if (!ui->msgField->text().isEmpty()) {
        m_chatClient->sendMessageToServer(ui->msgField->text());
        ui->msgField->clear();
    }
}

void ChatWidget::setupChatServer() {
    m_chatServer = new ChatServer;

    // connect needed before init to display system messages in the chat during initialization
    connect(m_chatServer, SIGNAL(sendMessageToChatUi(QString)),
                        this, SLOT(receivedMessage(QString)));
    m_chatServer->init();
}

void ChatWidget::setupChatClient() {
    // TEST
    m_chatClient = new ChatClient(QString("127.0.0.1"), 50885);
    // TEST

    connect(m_chatClient, SIGNAL(sendMessageToChatUi(QString)),
                        this, SLOT(receivedMessage(QString)));
    connect(m_chatClient->getChatCmds(), SIGNAL(cmdUpdateUserListView()),
                        this, SLOT(updateNicknamesListView()));
}

void ChatWidget::receivedMessage(const QString &msg) {
    QString htmlMsg = QString("<div style=\" white-space: pre-wrap;\">%1</div>").arg(msg);
    ui->msgList->append(htmlMsg);
}

void ChatWidget::updateNicknamesListView() {
    m_NicknamesListModel->setStringList(AbstractChatCmd::getUsersListClient()->keys());
}

void ChatWidget::rollDice(QString dice, bool hidden){
    QString msg = QString("/roll %1").arg(dice);

    if (hidden) {
        msg += QString(" | %2").arg(m_chatClient->getUser()->getNickname());
    }

     m_chatClient->sendMessageToServer(msg);
}
