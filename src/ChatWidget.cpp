#include <QMenu>
#include "ChatWidget.h"
#include "ui_ChatWidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    ui->nicknamesListView->setContextMenuPolicy(Qt::CustomContextMenu);

    // for right-clicking on the user list
    connect(ui->nicknamesListView, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));

    // Chat nicknames list
    m_NicknamesListModel = new QStringListModel;
    ui->nicknamesListView->setModel(m_NicknamesListModel);
}

ChatWidget::~ChatWidget()
{
    delete ui;
    delete m_NicknamesListModel;
}

/**
 * @brief ChatWidget::on_msgField_returnPressed
 *
 * Clean input field
 */
void ChatWidget::on_msgField_returnPressed()
{
    if (!ui->msgField->text().isEmpty()) {
        m_ChatClient->sendMessageToServer(ui->msgField->text());
        ui->msgField->clear();
    }
}

void ChatWidget::setupChatServer(ChatServer *chatServer) {
    m_ChatServer = chatServer;

    connect(m_ChatServer, SIGNAL(sendMessageToChatUi(QString)),
                        this, SLOT(receivedMessage(QString)));
}

void ChatWidget::setupChatClient(ChatClient *chatClient) {
    m_ChatClient = chatClient;

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




void ChatWidget::ShowContextMenu(const QPoint& pos){
    QPoint globalPos = this->mapToGlobal(pos);
    QString msg;
    QMenu menu;
    menu.addAction(tr("Lancer les dés"));

    QAction* selectedItem = menu.exec(globalPos);
    if (selectedItem)
    {
        emit requestDice(msg);
        int index = ui->nicknamesListView->currentIndex().row();
        msg += QString("| %1").arg(m_NicknamesListModel->stringList().at(index));
        m_ChatClient->sendMessageToServer(msg);
    }

}
