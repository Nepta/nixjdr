#include "TokenItem.h"

TokenItem::TokenItem(QString path, QString name) : DBItem("sprite"){
	icon_.addFile(path);
	name_ = name;
}

QIcon& TokenItem::icon(){
	return icon_;
}

QString& TokenItem::name(){
	return name_;
}
