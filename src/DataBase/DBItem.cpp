#include "DBItem.h"
#include <QDebug>

DBItem::DBItem(){
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

int DBItem::appendValue(QString newValue){
	listValue_.append(newValue);
	return listValue_.size();
}

int DBItem::appendValue(int newValue){
    return appendValue(QString::number(newValue));
}
