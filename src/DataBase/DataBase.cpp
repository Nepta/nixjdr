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
	QString queryString = QString("insert into %1 values(\'%2\', %3)")
			.arg(item.type())
			.arg(item.value(0))
			.arg(item.value(1))
	;
	QSqlQuery query(queryString);
	query.exec();
}

DataBase::~DataBase(){
	db_.close();
//	QFile::remove(dbName_ + ".sqlite"); // maybe a bad idea ?
}
