#include "TokenItem.h"
#include "DataBase/QueryType.h"

TokenItem::TokenItem(QString path, QString name) : DBItem("sprite"){
	icon_.addFile(path);
	name_ = name;
	appendValue("name",name);
	appendValue("path",path);
}

QIcon& TokenItem::icon(){
	return icon_;
}

QString& TokenItem::name(){
	return name_;
}
