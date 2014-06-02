#include <QList>
#include <QDebug>

#include "Database/Repository/RepositoryManager.h"
#include "Database/QueryBuilder.h"
#include "Database/DBItemList.h"

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

void TokenMenu::initTokenMenu(Database *db) {
    setDatabase(db);

    // Retrieve TokenItems from the database
    QList<TokenItem*> tokenItems = RepositoryManager::s_TokenItemRepository.getTokenItems(db_);
    for (TokenItem *tokenItem : tokenItems) {
        ui->m_tokenList->addItem(tokenItem);
    }

    ui->m_tokenList->setCurrentItem(ui->m_tokenList->item(0));
}

Ui::TokenMenu *TokenMenu::getUi() {
    return ui;
}

void TokenMenu::on_tokenButton_clicked()
{
    // TODO filePath and size are hard-coded
    QString text = ui->inputSearchField->text();
    QString filePath("resource/keroro.png");
    int size = 32;
    bool custom = true;

    // Check if the list already contains a token with the same text before insertion.
    QList<QListWidgetItem*> items = ui->m_tokenList->findItems(text, Qt::MatchExactly);
    if (items.empty()) {
        TokenItem *item = new TokenItem(filePath, text, size, custom);

        // push the item into the database
        RepositoryManager::s_TokenItemRepository.insertTokenItem(item, db_);

        // add the item to the tokenList
        ui->m_tokenList->addItem(item);
        ui->m_tokenList->setCurrentItem(item);
    }
    else {
        // TODO display a notification that an item with the given text already exists.
        qDebug() << tr("Un jeton portant ce nom existe déjà.");
    }
}
