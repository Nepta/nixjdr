#ifndef DBITEM_H
#define DBITEM_H
#include <QString>
#include <QHash>

class DBItem {
private:
    QString tableName_;
    QHash<QString, QString> columnsValues_;

public:
    DBItem(QString tableName = "");
	QHash<QString, QString>& getHashMap();

    void appendValue(QString columName,QString newValue);
    void appendValue(QString columName, int newValue);
};

#endif // DBITEM_H
