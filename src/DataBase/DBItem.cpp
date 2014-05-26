#include "DBItem.h"
#include <QDebug>

DBItem::DBItem(QueryType::TYPE type) : type_(type){
}

QString DBItem::tableAffected(){
	return targetTable_;
}

void DBItem::tableAffected(QString targetTable){
	targetTable_ = targetTable;
}

QString DBItem::value(int index){
	return listValue_.at(index);
}

int DBItem::pushDB(QString newValue){
	listValue_.append(newValue);
	return listValue_.size();
}

int DBItem::pushDB(int newValue){
	return pushDB(QString::number(newValue));
}

QString DBItem::buildQuery(){
	QString queryString = type().keyword();
	QString nextKeyword;
	switch(type().type()){
		case QueryType::insert:
			queryString += " %3 %1 %2";
			nextKeyword = "values";
			break;
		case QueryType::select:
			queryString += " %1 %2 %3";
			nextKeyword = "from";
			break;
		default:
			queryString = "--";
			break;
	}
	qDebug() << "queryString: " << queryString;
	qDebug() << "nextKeyword: " << nextKeyword;
	qDebug() << "tableAffected " << tableAffected();
	return queryString.arg("name,path").arg(nextKeyword).arg(tableAffected());
}

QueryType DBItem::type(){
	return type_;
}

