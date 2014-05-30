#ifndef TOKENITEM_H
#define TOKENITEM_H

#include <QIcon>
#include <Database/DBItem.h>

class TokenItem : public DBItem {
private:
	QIcon icon_;
    QString name_;
    int size_;

    void construct(QString path, QString name, int size);

public:
    TokenItem(QString path, QString name, int size);
    TokenItem(DBItem item);
    QIcon icon();
    QString name();
    int size();
};

#endif // TOKENITEM_H
