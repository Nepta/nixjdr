#ifndef DBITEM_H
#define DBITEM_H

#include <QString>
#include <QHash>
#include <QVariant>

#include "Network/Serializable/Serializable.h"

class DBItem : public Serializable {
public:
    DBItem(int id = 0);

    void appendValue(QString columName, QVariant newValue);
    void appendValue(QString columName, int newValue);
    void setId(int id);

    virtual QByteArray serialize();
    virtual void unserialize(QByteArray& data);

    QHash<QString, QVariant> &getHashMap();
    int id();

protected:
    int id_;
    QHash<QString, QVariant> columnsValues_;
};

#endif // DBITEM_H
