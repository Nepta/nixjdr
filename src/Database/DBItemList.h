#ifndef DBITEMLIST_H
#define DBITEMLIST_H

#include <QList>
#include "DBItem.h"


template <class T>

/**
 * @brief The DBItemList class contains a QList containing DBitems. This class provides a way of
 * creating a QList containing instances of classes inheriting DBItem.
 */
class DBItemList
{
public:
    DBItemList(QList<DBItem> dbItems) {
        dbItems_ = dbItems;
    }

    QList<T*> construct() {
        QList<T*> resultItems;

        for (DBItem dbItem : dbItems_) {
            T* item = new T(dbItem);
            resultItems.append(item);
        }

        return resultItems;
    }

    QList<DBItem> getList() {
        return dbItems_;
    }

private:
    QList<DBItem> dbItems_;
};

#endif // DBITEMLIST_H
