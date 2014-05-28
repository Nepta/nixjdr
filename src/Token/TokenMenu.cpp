#include <QPixmap>
#include <QPainter>
#include <QSqlQuery>
#include "DataBase/QueryBuilder.h"

#include "TokenMenu.h"
#include "ui_TokenMenu.h"

TokenMenu::TokenMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TokenMenu)
{
    ui->setupUi(this);
    QueryBuilder builder;
    builder.select("name, path")
           ->from("sprite");

    QSqlQuery query = builder.getQuery();

	 while(query.next()){
		 QString name = query.value(0).toString();
		 QString path = query.value(1).toString();
		 TokenItem item(path, name);
		 ui->m_tokenList->appendCustomItem(item);
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
