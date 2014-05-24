#include <QMenu>
#include "ChatWidget.h"
#include "ui_ChatWidget.h"
#include <QDebug>

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    ui->nicknamesListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->nicknamesListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    // for right-clicking on the user list
    connect(ui->nicknamesListWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));
}

ChatWidget::~ChatWidget()
{
    delete ui;
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
    ui->nicknamesListWidget->clear();
    foreach (QString user, AbstractCmd::getUsersListClient()->keys()) {
        ui->nicknamesListWidget->addItem(user);
    }

}

void ChatWidget::rollDice(QString dice, bool hidden){
    QString msg = QString("/roll %1").arg(dice);

    if (hidden) {
        msg += QString(" | %2").arg(m_ChatClient->getUser()->getNickname());
    }

     m_ChatClient->sendMessageToServer(msg);
}



void ChatWidget::ShowContextMenu(const QPoint& pos){

    QMenu menu;
    QPoint globalPos = this->mapToGlobal(pos);
    QList<QListWidgetItem *> selectedItems = ui->nicknamesListWidget->selectedItems();

    QAction* throwDice = menu.addAction(tr("Lancer les dés"));
    QAction* sendMessage = menu.addAction(tr("Envoyer un message"));

    QAction* selectedItem = menu.exec(globalPos);

    if (selectedItem == throwDice){
        sendRolledDiceToQWidgetItemList(selectedItems);
    }
    else if(selectedItem == sendMessage){
        prepareWhispForListOfQWidgetItem(selectedItems);
    }

}

void ChatWidget::sendRolledDiceToQWidgetItemList(QList<QListWidgetItem *> list){
    QString msg;
    emit requestDice(msg);

    foreach (QListWidgetItem *item, list) {
        msg += QString(" |%1").arg(item->text());
    }

    m_ChatClient->sendMessageToServer(msg);
    setFocusToChat();
}

void ChatWidget::prepareWhispForListOfQWidgetItem(QList<QListWidgetItem *> list){
    QString msg = "/w ";

    foreach(QListWidgetItem * item, list){
        msg += QString("%1 | ").arg(item->text());
    }

    msg.chop(1);
    msg.append(" ");

    ui->msgField->setText(msg);
    setFocusToChat();
}

void ChatWidget::setFocusToChat(){
    ui->msgField->setFocus();
    ui->tabWidget->setCurrentIndex(0);
}
