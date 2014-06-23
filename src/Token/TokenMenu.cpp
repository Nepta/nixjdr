#include <QList>
#include <QMenu>
#include <QAction>

#include "Database/Repository/RepositoryManager.h"
#include "Database/QueryBuilder.h"
#include "Database/DBItemList.h"

#include "GameObjects/GameObjectDialog.h"

#include "Network/TokenMenuCodes.h"
#include "StyleSheet.h"
#include "TokenMenu.h"
#include "ui_TokenMenu.h"

TokenMenu::TokenMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TokenMenu)
{
    ui->setupUi(this);

    initTokenMenu();
}

TokenMenu::~TokenMenu()
{
    delete ui;
}

void TokenMenu::initTokenMenu() {
    // Retrieve TokenItems from the database
    QList<TokenItem*> tokenItems = RepositoryManager::s_TokenItemRepository.getTokenItems();
    for (TokenItem *tokenItem : tokenItems) {
        ui->m_tokenList->addItem(tokenItem);

        if (tokenItem->isSpecial()) {
            tokenItem->setHidden(true);
        }
    }

    ui->m_tokenList->setCurrentItem(ui->m_tokenList->item(0));
}

Ui::TokenMenu *TokenMenu::getUi() {
    return ui;
}

void TokenMenu::addItem(QListWidgetItem *item) {
    ui->m_tokenList->addItem(item);
}

/**
 * @brief TokenMenu::on_tokenButton_clicked Displays a context menu which lets the user choose
 * between the creation of a custom TokenItem and the creation of a TokenItem possessing a
 * GameObject.
 */
void TokenMenu::on_tokenButton_clicked()
{
    QMenu menu;

    QAction* createCustomToken = menu.addAction(tr("Créer un jeton personnalisé"));
    QAction* createGameObject = menu.addAction(tr("Créer un élément de jeu"));

    QAction* selectedItem = menu.exec(QCursor::pos());
    if (selectedItem == createCustomToken) {
        QString text = ui->inputSearchField->text();
        addCustomToken(text);
    }
    else if (selectedItem == createGameObject) {
        GameObjectDialog gameObjectDlg;
        gameObjectDlg.exec();
        GameObject *gameObject = gameObjectDlg.getGameObject();
        QString path = gameObjectDlg.getPath();
        gameObjectDlg.close();

        if (gameObject != NULL) {
            // Push the game object into the database
            RepositoryManager::s_GameObjectRepository.insertGameObject(gameObject);

            addCustomToken(gameObject->getName(), path, gameObject);
        }
    }
}

void TokenMenu::addCustomToken(QString text, QString filePath, GameObject *gameObject) {
    int size = 32;

    addToken(text, filePath, size, true, gameObject);
}

void TokenMenu::addToken(QString text, QString filePath, int size, bool custom,
    GameObject *gameObject)
{
    // Check if the list already contains a token with the same text before insertion.
    QList<QListWidgetItem*> items = ui->m_tokenList->findItems(text, Qt::MatchExactly);
    if (items.empty()) {
        TokenItem *item = new TokenItem(filePath, text, size, custom);
        item->setGameObject(gameObject);

        // push the item into the database
        RepositoryManager::s_TokenItemRepository.insertTokenItem(item);

        // add the item to the tokenList
        ui->m_tokenList->addItem(item);
        ui->m_tokenList->setCurrentItem(item);

        // Notifies everyone that an item has been added
        QString msg = QString("%1").arg(item->id());
        m_SenderClient->sendMessageToServer(msg, (quint16) TokenMenuCodes::ADD_TOKEN);
    }
    else {
        emit sendNotification(QString("Un jeton nommé %1 existe déjà.").arg(text));
    }
}

void TokenMenu::editTokenCharacter(TokenItem *tokenItem) {
    GameObject *gameObject = tokenItem->getGameObject();
    Character *character = dynamic_cast<Character*>(gameObject);

    if (character != NULL) {
        GameObjectDialog gameObjectDlg(character);
        gameObjectDlg.exec();
        gameObjectDlg.close();

        // Update the Character in the database
        RepositoryManager::s_CharacterRepository.updateCharacter(character);

        // Update the character for all the clients
        QString msg = QString("%1").arg(tokenItem->id());
        m_SenderClient->sendMessageToServer(msg, (quint16) TokenMenuCodes::UPDATE_TOKEN);
    }
}

void TokenMenu::on_m_tokenList_customContextMenuRequested(const QPoint &pos) {
    QPoint globalPos = mapToGlobal(pos);
    QMenu menu;

    QAction *editAction = menu.addAction(tr("Editer l'élément de jeu"));
    QListWidgetItem *item = ui->m_tokenList->itemAt(pos);
    TokenItem *tokenItem = dynamic_cast<TokenItem*>(item);

    if (tokenItem == NULL || tokenItem->getGameObject() == NULL) {
        editAction->setEnabled(false);
    }

    QAction *selectedAction = menu.exec(globalPos);
    if (selectedAction == editAction) {
        editTokenCharacter(tokenItem);
    }
}

TokenList *TokenMenu::getTokenList() {
    return ui->m_tokenList;
}

void TokenMenu::on_inputSearchField_textChanged(const QString &arg1)
{
    for(int i=0; i<ui->m_tokenList->count(); i++){
        QListWidgetItem *item = ui->m_tokenList->item(i);
        if(item->text().left(arg1.length()) == arg1){
            item->setHidden(false);
        }
        else{
            item->setHidden(true);
        }
    }
}
