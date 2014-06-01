#ifndef DBITEM_H
#define DBITEM_H

#include <QString>
#include <QHash>
#include <QVariant>

class DBItem {
protected:
    int id_;
    QHash<QString, QVariant> columnsValues_;

public:
    DBItem(int id = 0);

    void appendValue(QString columName, QVariant newValue);
    void appendValue(QString columName, int newValue);
    void setId(int id);

    QHash<QString, QVariant> &getHashMap();
    int id();
};

#endif // DBITEM_H
