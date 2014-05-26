#ifndef QUERYTYPE_H
#define QUERYTYPE_H
#include <QString>

class QueryType{
public:
	enum TYPE{
		insert,
		select
	};

private:
	TYPE type_;
	QString keyword_;

public:
	QueryType(TYPE type);
	QString keyword();
	TYPE type();

};

#endif // QUERYTYPE_H
