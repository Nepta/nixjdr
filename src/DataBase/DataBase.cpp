#include "DataBase.h"
#include <QSqlRecord>
#include <iostream>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "QueryBuilder.h"

DataBase::DataBase(const QString dbName, const QString& serverAddress, const int& serverPort) {
	db_ = QSqlDatabase::addDatabase("QPSQL");
	db_.setUserName("jdr");
    db_.setDatabaseName(dbName);
	db_.setPassword("password");
    db_.setHostName(serverAddress);
    db_.setPort(serverPort);
	db_.open();
}

DataBase::~DataBase(){
	db_.close();
}

void DataBase::addItem(DBItem& item){
	//table map(name,tileSize)
	QueryBuilder builder;
	QString columns;
	QString values;
	for(QString key : item.getHashMap().keys()){
		columns += key + ",";
		values += item.getHashMap().value(key) + ",";

	}
	columns.chop(1);
	values.chop(1);
	builder.insertInto(item.tableAffected(),columns)
			->values(values);

	QSqlQuery query = builder.getQuery();
	query.exec();
	emit newItemInDB(new DBItem(item));
}
