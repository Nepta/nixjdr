#include <QMenu>
#include "ChatWidget.h"
#include "ui_ChatWidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    ui->nicknamesListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->nicknamesListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    // right-clicking on the user list shows a context menu
    connect(ui->nicknamesListWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::on_msgField_returnPressed()
{
    if (!ui->msgField->text().isEmpty()) {
        m_SenderClient->sendMessageToServer(ui->msgField->text());
        ui->msgField->clear();
    }
}

void ChatWidget::setSenderClient(SenderClient *senderClient) {
    SenderHandler::setSenderClient(senderClient);

    ChatClient *chatClient = dynamic_cast<ChatClient*>(m_SenderClient);

    // TODO se paser de connects (le chatclient connait le chatwidget)
    connect(chatClient, SIGNAL(sendMessageToChatUi(QString)),
                        this, SLOT(receivedMessage(QString)));
    connect(chatClient->getCommands(), SIGNAL(cmdUpdateUserListView()),
                        this, SLOT(updateNicknamesListView()));
}

void ChatWidget::setSenderServer(SenderServer *senderServer) {
    SenderHandler::setSenderServer(senderServer);

    ChatServer *chatServer = dynamic_cast<ChatServer*>(m_SenderServer);

    // TODO se passer de connects (le chatserver connait le chatwidget)
    connect(chatServer, SIGNAL(sendMessageToChatUi(QString)),
                        this, SLOT(receivedMessage(QString)));
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
        msg += QString(" |%1").arg(m_SenderClient->getUser()->getNickname());
    }

    m_SenderClient->sendMessageToServer(msg);
}



void ChatWidget::ShowContextMenu(const QPoint& pos){

    QMenu menu;
    QPoint globalPos = this->mapToGlobal(pos);
    QList<QListWidgetItem *> selectedItems = ui->nicknamesListWidget->selectedItems();

    QAction* throwDice = menu.addAction(tr("Lancer les dés"));
    QAction* sendMessage = menu.addAction(tr("Envoyer un message"));

    QAction* selectedItem = menu.exec(globalPos);

    if (selectedItem == throwDice){
        sendRolledDiceToUsers(selectedItems);
    }
    else if(selectedItem == sendMessage){
        prepareWhispUsers(selectedItems);
    }

}

void ChatWidget::sendRolledDiceToUsers(QList<QListWidgetItem *> list){
    QString msg;
    emit requestDice(msg);

    foreach (QListWidgetItem *item, list) {
        msg += QString(" |%1").arg(item->text());
    }

    m_SenderClient->sendMessageToServer(msg);
    setFocusToChat();
}

void ChatWidget::prepareWhispUsers(QList<QListWidgetItem *> list){
    QString msg = "/w ";

    foreach(QListWidgetItem * item, list) {
        if (list.indexOf(item) == 0) { // first item
            msg += QString(" %1 ").arg(item->text());
        } else {
            msg += QString("| %1 ").arg(item->text());
        }
    }

    ui->msgField->setText(msg);
    setFocusToChat();
}

void ChatWidget::setFocusToChat(){
    ui->msgField->setFocus();
    ui->tabWidget->setCurrentIndex(0);
}
