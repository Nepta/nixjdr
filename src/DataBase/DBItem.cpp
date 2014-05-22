#include "DBItem.h"

DBItem::DBItem(QString type){
	type_	= type;
}

QString DBItem::type(){
	return type_;
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
