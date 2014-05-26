#ifndef QUERYTYPE_H
#define QUERYTYPE_H
#include <QString>

class QueryType{
	QString keyword_;

public:
	enum TYPE{
		insert,
		select
	};
	QueryType(TYPE type);
	QString keyword();

};

#endif // QUERYTYPE_H
