#include <QList>
#include <QMenu>
#include <QAction>
#include <QDirIterator>

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
}

TokenMenu::~TokenMenu()
{
    delete ui;
}

/**
 * @brief TokenMenu::initTokenMenu Initializes the TokenMenu.
 * @remarks Must only be called after the SenderClient has been initialized.
 */
void TokenMenu::initTokenMenu() {
    if (RepositoryManager::s_TokenItemRepository.isEmpty()) {
        initTokenMenuPush();
    }
    else {
        initTokenMenuPull();
    }
}

/**
 * @brief TokenMenu::initTokenMenuPush Initializes the TokenMenu and the database with resources
 * coming from the "resource/TokenMenu/" folder.
 */
void TokenMenu::initTokenMenuPush() {
    QDirIterator dirIt("resource/TokenMenu", QDirIterator::Subdirectories);

    while(dirIt.hasNext()) {
        QString filePath = dirIt.next();
        QString suffix = dirIt.fileInfo().suffix();

        if (!suffix.isEmpty()) {
            QString name = dirIt.fileInfo().baseName();
            bool special = filePath.contains("Special");

            // TODO hard coded size
            TokenItem *item = addToken(name, filePath, 32, false, special);
            item->setHidden(special);
        }
    }
}

/**
 * @brief TokenMenu::initTokenMenuPull Initializes the TokenMenu with data coming from the database.
 */
void TokenMenu::initTokenMenuPull() {
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

TokenItem *TokenMenu::addCustomToken(QString text, QString filePath, GameObject *gameObject) {
    int size = 32;

    return addToken(text, filePath, size, true, false, gameObject);
}

TokenItem* TokenMenu::addToken(QString text, QString filePath, int size, bool custom, bool special,
    GameObject *gameObject)
{
    // Check if the list already contains a token with the same text before insertion.
    QList<QListWidgetItem*> items = ui->m_tokenList->findItems(text, Qt::MatchExactly);
    if (items.empty()) {
        TokenItem *item = new TokenItem(filePath, text, size, custom, special);

        if (!item->isPixLoaded()) {
            emit sendNotification(QString("L'image spécifiée par le chemin %1 n'a pas pu être chargée.")
                .arg(filePath));
        }

        item->setGameObject(gameObject);

        // push the item into the database
        RepositoryManager::s_TokenItemRepository.insertTokenItem(item);

        // add the item to the tokenList
        ui->m_tokenList->addItem(item);
        ui->m_tokenList->setCurrentItem(item);

        // Notifies everyone that an item has been added
        QString msg = QString("%1").arg(item->id());
        m_SenderClient->sendMessageToServer(msg, (quint16) TokenMenuCodes::ADD_TOKEN);

        return item;
    }
    else {
        emit sendNotification(QString("Un jeton nommé %1 existe déjà.").arg(text));

        return NULL;
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
        TokenItem *tokenItem = dynamic_cast<TokenItem*>(item);

        if(item->text().left(arg1.length()) == arg1 && !tokenItem->isSpecial()){
            item->setHidden(false);
        }
        else{
            item->setHidden(true);
        }
    }
}
