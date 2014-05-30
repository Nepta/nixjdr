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

    /*QPixmap pix;
    pix.load(filePath);

    QPainter painter(&pix);
    QPainterPath painterPath;

    painterPath.addText(QPointF(1, pix.height()), QFont("Arial", 15, QFont::Bold), text);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPath(painterPath);*/

    // TODO set custom to true
    // TODO in TokenItem if custom -> bouger tout ce qu'il y a plus haut dans une méthode
    // createCustomIcon dans la classe TokenItem() + appel
    TokenItem *item = new TokenItem(filePath, text, size);
    ui->m_tokenList->addItem(item);

    //ui->m_tokenList->appendCustomItem(QIcon(pix), text);
    //ui->m_tokenList->setCurrentRow(ui->m_tokenList->count()-1);
    ui->m_tokenList->setCurrentItem(item);
}
