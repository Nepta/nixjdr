#include "QueryType.h"

QueryType::QueryType(TYPE type) : type_(type){
	switch(type){
		case TYPE::insert:
			keyword_ = "insert into";
			break;
		case TYPE:: select:
			keyword_ = "select";
			break;
		default:
			keyword_ = "--";
			break;
	}
}

QString QueryType::keyword(){
	return keyword_;
}

QueryType::TYPE QueryType::type(){
	return type_;
}
