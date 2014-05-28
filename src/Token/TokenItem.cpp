#include "TokenItem.h"
#include "DataBase/QueryType.h"

TokenItem::TokenItem(QString path, QString name) : DBItem(){
	icon_.addFile(path);
	name_ = name;
}

QIcon& TokenItem::icon(){
	return icon_;
}

QString& TokenItem::name(){
	return name_;
}
