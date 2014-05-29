#include <QPixmap>
#include <QPainter>
#include <QSqlQuery>
#include "DataBase/Repository/SpriteRepository.h"
#include "DataBase/QueryBuilder.h"
#include "DataBase/DBItemList.h"
#include "TokenMenu.h"
#include "ui_TokenMenu.h"

TokenMenu::TokenMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TokenMenu)
{
    ui->setupUi(this);

    QueryBuilder qb = SpriteRepository::getSprites();
    DBItemList<TokenItem> dbItems(db_->pull(qb));
    QList<TokenItem> tokenItemList = dbItems.construct();

    for (TokenItem tokenItem : tokenItemList) {
        ui->m_tokenList->appendCustomItem(tokenItem);
    }

    ui->m_tokenList->setCurrentItem(ui->m_tokenList->item(0));
}

TokenMenu::~TokenMenu()
{
    delete ui;
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
