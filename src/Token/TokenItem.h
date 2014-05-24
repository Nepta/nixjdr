#ifndef TOKENITEM_H
#define TOKENITEM_H
#include <QIcon>
#include <DataBase/DBItem.h>

class TokenItem : public DBItem{
	QIcon icon_;
	QString name_;
public:
	TokenItem(QString path, QString name);
	QIcon& icon();
	QString& name();
};

#endif // TOKENITEM_H
