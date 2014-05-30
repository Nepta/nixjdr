#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include "TokenItem.h"

TokenItem::TokenItem(QString path, QString text, int size, bool custom, bool special) :
    DBItem("tokenitem")
{
    construct(path, text, size, custom, special);
}

TokenItem::TokenItem(DBItem item) :
    DBItem("tokenitem")
{
    QHash<QString, QString> itemHashMap = item.getHashMap();

    int id = itemHashMap.value("id").toInt();
    QString text = itemHashMap.value("text");
    QString path =  itemHashMap.value("path");
    int size = itemHashMap.value("size").toInt();
    bool custom = itemHashMap.value("custom").toInt();
    bool special = itemHashMap.value("special").toInt();

    construct(id, path, text, size, custom, special);
}

void TokenItem::construct(int id, QString path, QString text, int size, bool custom, bool special) {
    id_ = id;
    construct(path, text, size, custom, special);
}

void TokenItem::construct(QString path, QString text, int size, bool custom, bool special) {
    setText(text);
    path_ = path;
    size_ = size;
    custom_ = custom;
    special_ = special;

    if (custom) {
        setCustomIcon(path, text);
    } else {
        setIcon(QIcon(path));
    }
}

/**
 * @brief TokenItem::setCustomIcon Sets the QIcon of this TokenItem to the image pointed by path
 * and a text added in front of it.
 * @param path Filepath pointing to the image to use for the icon.
 * @param text Text to add in front of the image.
 */
void TokenItem::setCustomIcon(QString path, QString text) {
    QPixmap pix;
    pix.load(path);

    QPainter painter(&pix);
    QPainterPath painterPath;

    painterPath.addText(QPointF(1, pix.height()), QFont("Arial", 15, QFont::Bold), text);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPath(painterPath);

    setIcon(QIcon(pix));
}

QString TokenItem::path() {
    return path_;
}

int TokenItem::size() {
    return size_;
}

bool TokenItem::isCustom() {
    return custom_;
}

bool TokenItem::isSpecial() {
    return special_;
}
