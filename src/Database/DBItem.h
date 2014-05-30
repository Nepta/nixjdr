#ifndef DBITEM_H
#define DBITEM_H
#include <QString>
#include <QHash>

class DBItem {
protected:
    QString tableName_;
    int id_;
    QHash<QString, QString> columnsValues_;

public:
    DBItem(QString tableName = "", int id = 0);

    void appendValue(QString columName,QString newValue);
    void appendValue(QString columName, int newValue);
    void setId(int id);

    QHash<QString, QString>& getHashMap();
    int id();
};

#endif // DBITEM_H
