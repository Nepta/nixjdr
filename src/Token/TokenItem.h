#ifndef TOKENITEM_H
#define TOKENITEM_H

#include <QIcon>
#include <QListWidgetItem>

#include "GameObjects/GameObject.h"
#include "Database/DBItem.h"

class TokenItem : public QListWidgetItem, public DBItem {
private:
    int size_;
    bool custom_;
    bool pixLoaded_;

    /**
     * @brief special_ A special TokenItem is used for specific cases (e.g. FoWLayer sprites).
     * It should not be displayed in the TokenMenu's list.
     */
    bool special_;
    GameObject *gameObject_;

    void construct(int id, QString path, QString text, int size, bool custom, bool special);
    void construct(QString path, QString text, int size, bool custom, bool special);
    void construct(int id, QIcon icon, QString text, int size, bool custom, bool special);
    void construct(QDataStream *stream);

public:
    TokenItem(QString path, QString text, int size, bool custom = false, bool special = false);
    TokenItem(const QByteArray& data);
    TokenItem(DBItem item);
    TokenItem(QDataStream *stream);

    QByteArray toQByteArray();
    void toQByteArray(QDataStream *stream);

    QString path();
    QByteArray iconPixmapData();
    int size();
    bool isCustom();
    bool isSpecial();
    bool isPixLoaded();
    GameObject *gameObject();

    GameObject *getGameObject();
    void setCustomIcon(QString path, QString text);
    void setIcon(QString path);
    void setGameObject(GameObject *gameObject);
};

#endif // TOKENITEM_H
