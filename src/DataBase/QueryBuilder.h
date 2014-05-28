#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include "DataBase.h"

class QueryBuilder{
public:
	QueryBuilder();
	QString QueryBuilder::buildQuery(QueryType type);
};

#endif // QUERYBUILDER_H
