#include "DataBase.h"
#include <QSqlRecord>
#include <iostream>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

DataBase::DataBase(const QString dbName, const QString& serverIpAddress){
	dbName_ = dbName;
	db_ = QSqlDatabase::addDatabase("QPSQL");
	db_.setUserName("jdr");
	db_.setDatabaseName("jdrDB");
	db_.setPassword("password");
	db_.setHostName(serverIpAddress);
	db_.open();
	DBItem *test = new DBItem(QueryType::select);
	test->tableAffected("sprite");
	qDebug() << "test: " << test->buildQuery();
	delete test;
	if(serverIpAddress == "127.0.0.1"){
		initDB();
	}
}

void DataBase::initDB(){
	QSqlQuery query("create table Map(path varchar(80), tileSize integer)");
	query.exec();
}

void DataBase::addItem(DBItem& item){
	//table map(name,tileSize)
	QString queryString = item.buildQuery();
	QSqlQuery query(queryString);
	query.exec();
	emit newItemInDB(new DBItem(item));
}

DataBase::~DataBase(){
	db_.close();
//	QFile::remove(dbName_ + ".sqlite"); // maybe a bad idea ?
}
