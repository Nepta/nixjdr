#include "DBItem.h"

DBItem::DBItem(QueryType::TYPE type) : type_(type){
}

QString DBItem::tableAffected(){
	return targetTable_;
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

QString DBItem::queryInsert(){
	QString queryString = QString("insert into %1 values(\'%2\', %3)")
			.arg(this->tableAffected())
			.arg(this->value(0))
			.arg(this->value(1))
	;
	return queryString;
}
