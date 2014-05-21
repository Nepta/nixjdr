#include "DataBase.h"
#include <iostream>

DataBase::DataBase(const QString dbName){
	dbName_ = dbName;
	db_ = QSqlDatabase::addDatabase("QSQLITE");
	db_.setDatabaseName(dbName_ + ".sqlite");
	db_.open();
}

DataBase::~DataBase(){
	db_.close();
	QFile::remove(dbName_ + ".sqlite"); // maybe a bad idea ?
}
