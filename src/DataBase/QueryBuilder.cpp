#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(){
}

QString QueryBuilder::buildQuery(QueryType type){
	QString queryString = type.keyword();
	switch(type.type()){
		case QueryType::insert:
			queryString += "insert into %2 %1 values ()";
			break;
		case QueryType::select:
			queryString += "select %2 from %1";
			break;
		default:
			queryString = "--";
			break;
	}
	return queryString.arg(tableAffected()).arg("name,path");
}
