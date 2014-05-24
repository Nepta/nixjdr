#include "TokenMenu.h"
#include "ui_TokenMenu.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

TokenMenu::TokenMenu(QWidget *parent) :
	QWidget(parent), ui(new Ui::TokenMenu){

	ui->setupUi(this);
	QSqlQuery query("select name,path from sprite");
	while(query.next()){
		QString name = query.value(0).toString();
		QString path = query.value(1).toString();
		ui->m_tokenList->addItem(new QListWidgetItem(QIcon(path), name));
	}
	ui->m_tokenList->setCurrentItem(ui->m_tokenList->item(0));
}

TokenMenu::~TokenMenu(){
	delete ui;
}

Ui::TokenMenu *TokenMenu::getUi() {
    return ui;
}
