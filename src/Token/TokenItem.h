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
    bool custom_;

    void construct(int id, QString path, QString text, int size, bool custom);
    void construct(QString path, QString text, int size, bool custom);

public:
    TokenItem(QString path, QString text, int size, bool custom = false);
    TokenItem(DBItem item);

    QString path();
    int size();
    bool isCustom();

    void setCustomIcon(QString path, QString text);
};

#endif // TOKENITEM_H
