#include <QPixmap>
#include <QPainter>
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

    // Example of insertion in the database (TODO remove this example)
    TokenItem item("resource/flandre.png", "test", 32);
    int id = TokenItemRepository::insertTokenItem(&item, db_); // retrieve the id set by the db
    item.setId(id);

    // Retrieve TokenItems from the database
    QList<TokenItem> tokenItems = TokenItemRepository::getTokenItems(db_);
    for (TokenItem tokenItem : tokenItems) {
        ui->m_tokenList->appendCustomItem(tokenItem);
    }

    ui->m_tokenList->setCurrentItem(ui->m_tokenList->item(0));
}

Ui::TokenMenu *TokenMenu::getUi() {
    return ui;
}

void TokenMenu::on_tokenButton_clicked()
{
    QPixmap pix;
    pix.load("resource/keroro.png");

    QPainter painter(&pix);
    QString text = ui->inputSearchField->text();
    QPainterPath path;

    path.addText(QPointF(1, pix.height()), QFont("Arial", 15, QFont::Bold), text);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPath(path);

    ui->m_tokenList->appendCustomItem(QIcon(pix), text);
    ui->m_tokenList->setCurrentRow(ui->m_tokenList->count()-1);
}
