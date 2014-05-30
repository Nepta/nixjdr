#include <QSqlQuery>
#include "Database/Repository/TokenItemRepository.h"
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
    QList<TokenItem*> tokenItems = TokenItemRepository::getTokenItems(db_);
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

    TokenItem *item = new TokenItem(filePath, text, size, custom);

    // push the item to the database
    int id = TokenItemRepository::insertTokenItem(item, db_);
    item->setId(id);

    // add the item to the tokenList
    ui->m_tokenList->addItem(item);
    ui->m_tokenList->setCurrentItem(item);
}
