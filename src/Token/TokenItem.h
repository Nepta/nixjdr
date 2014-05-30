#ifndef TOKENITEM_H
#define TOKENITEM_H

#include <QIcon>
#include <Database/DBItem.h>
#include <QListWidgetItem>

class TokenItem : public QListWidgetItem, public DBItem {
private:
    //QIcon icon_;
    QString path_;
    //QString name_;
    int size_;

    void construct(int id, QString path, QString text, int size);
    void construct(QString path, QString text, int size);

public:
    TokenItem(QString path, QString text, int size);
    TokenItem(DBItem item);
    //QIcon icon();
    QString path();
    //QString name();
    int size();
};

#endif // TOKENITEM_H
