#include "DataBase.h"
#include <QSqlRecord>
#include <iostream>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "QueryBuilder.h"

DataBase::DataBase(const QString dbName, const QString& serverIpAddress){
	dbName_ = dbName;
	db_ = QSqlDatabase::addDatabase("QPSQL");
	db_.setUserName("jdr");
    db_.setDatabaseName(dbName);
	db_.setPassword("password");
	db_.setHostName("lune.hurata.fr");
	db_.setPort(45001);
	db_.open();
	if(serverIpAddress == "127.0.0.1"){
		initDB();
	}
}

void DataBase::initDB(){
	QSqlQuery query("create table Map(path varchar(80), tileSize integer)");
	query.exec();
}

/*void DataBase::addItem(DBItem& item){
	//table map(name,tileSize)
	QString queryString = item.buildQuery(QueryType(QueryType::insert));

    // TODO query builder

	QSqlQuery query(queryString);
	query.exec();
	emit newItemInDB(new DBItem(item));
}*/

DataBase::~DataBase(){
	db_.close();
}
