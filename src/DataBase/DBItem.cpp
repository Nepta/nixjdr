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

