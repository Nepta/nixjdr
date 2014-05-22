#include "DataBase.h"
#include <QSqlRecord>
#include <iostream>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlQuery>
#include <QDebug>

DataBase::DataBase(const QString dbName){
	dbName_ = dbName;
	db_ = QSqlDatabase::addDatabase("QSQLITE");
	db_.setDatabaseName(dbName_ + ".sqlite");
	bool isAlreadyDB = QFile::exists(dbName_ + ".sqlite");
	db_.open();
	if(!isAlreadyDB){
		initDB();
	}
}

void DataBase::initDB(){
	QSqlQuery query("create table Map(path vachar(80), tileSize integer)");
	query.exec();
}

void DataBase::addItem(DBItem& item){
	//table map(name,tileSize)
	QString queryString = QString("insert into %1 values(%2, %3)")
			.arg(item.type())
			.arg(item.value(0))
			.arg(item.value(1))
	;
	qDebug() << item.value(1);
	QSqlQuery query(queryString);
	query.exec();
}

DataBase::~DataBase(){
	db_.close();
//	QFile::remove(dbName_ + ".sqlite"); // maybe a bad idea ?
}
