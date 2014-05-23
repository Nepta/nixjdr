#include "TokenMenu.h"
#include "ui_TokenMenu.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

TokenMenu::TokenMenu(QWidget *parent) :
	QWidget(parent), ui(new Ui::TokenMenu){

	ui->setupUi(this);
	model_ = new QSqlQueryModel;
	qDebug() << "database query";
	model_->setQuery("select path,name from sprite");
	ui->m_tokenList->setModelColumn(0);
}

TokenMenu::~TokenMenu(){
	delete ui;
	delete model_;
}

Ui::TokenMenu *TokenMenu::getUi() {
    return ui;
}
