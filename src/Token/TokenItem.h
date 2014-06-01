#ifndef TOKENITEM_H
#define TOKENITEM_H

#include <QIcon>
#include <QListWidgetItem>

#include "Database/DBItem.h"

class TokenItem : public QListWidgetItem, public DBItem {
private:
    QString path_;
    int size_;
    bool custom_;

    /**
     * @brief special_ A special TokenItem is used for specific cases (e.g. FoWLayer sprites).
     * It should not be displayed in the TokenMenu's list.
     */
    bool special_;

    void construct(int id, QString path, QString text, int size, bool custom, bool special);
    void construct(QString path, QString text, int size, bool custom, bool special);

public:
    TokenItem(QString path, QString text, int size, bool custom = false, bool special = false);
    TokenItem(const QByteArray& data);
    TokenItem(DBItem item);

    QByteArray toQByteArray();

    QString path();
    int size();
    bool isCustom();
    bool isSpecial();

    void setCustomIcon(QString path, QString text);
};

#endif // TOKENITEM_H
