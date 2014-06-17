#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QByteArray>
#include <QVariant>

#include "Database/Repository/RepositoryManager.h"
#include "Database/Repository/GameObjectRepository.h"
#include "TokenItem.h"

TokenItem::TokenItem(QString path, QString text, int size, bool custom, bool special) :
    DBItem()
{
    gameObject_ = NULL;

    construct(path, text, size, custom, special);
}

/**
 * @brief TokenItem::TokenItem Constructs a TokenItem with information stored in a QByteArray.
 * @remarks Used in a drag&drop event to restore data previously stored in a QByteArray through the
 * toQByteArray() method.
 * @param data
 * @sa toQByteArray()
 */
TokenItem::TokenItem(const QByteArray& data) :
    DBItem()
{
    gameObject_ = NULL;

    QDataStream stream(data);
    construct(&stream);
}

TokenItem::TokenItem(QDataStream *stream) {
    gameObject_ = NULL;

    construct(stream);
}

TokenItem::TokenItem(DBItem item) :
    DBItem()
{
    columnsValues_ = item.getHashMap();

    int id = columnsValues_.value("id").toInt();
    QString text = columnsValues_.value("text").toString();
    QString path =  columnsValues_.value("path").toString();
    int size = columnsValues_.value("size").toInt();
    bool custom = columnsValues_.value("custom").toBool();
    bool special = columnsValues_.value("special").toBool();

    // Retrieve gameObject from the database
    int gameobjectid = columnsValues_.value("gameobjectid").toInt();
    if (gameobjectid != 0) {
        gameObject_ = RepositoryManager::s_CharacterRepository.getFullGameObject(gameobjectid);
    }
    else {
        gameObject_ = NULL;
    }

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

void TokenItem::construct(QDataStream *stream) {
    int id, size, gameObjectId;
    QString text, path;
    bool custom, special;

    *stream >> id >> text >> path >> size >> custom >> special >> gameObjectId;

    if (gameObjectId != 0) {
        gameObject_ = RepositoryManager::s_CharacterRepository.getFullGameObject(gameObjectId);
    }

    construct(id, path, text, size, custom, special);
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
    painter.setRenderHint(QPainter::Antialiasing); // TODO test
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

GameObject *TokenItem::gameObject() {
    return gameObject_;
}

/**
 * @brief TokenItem::toQByteArray Stores the current instance of TokenItem in a QByteArray.
 * @remarks Used in drag&drop events to pass a TokenItem through the MimeData.
 * @return QByteArray containing sufficient information about the TokenItem to reconstruct it.
 */
QByteArray TokenItem::toQByteArray() {
    QByteArray out;
    QDataStream stream(&out, QIODevice::WriteOnly);

    toQByteArray(&stream);

    return out;
}

void TokenItem::toQByteArray(QDataStream *stream) {
    *stream << id_ << text() << path_ << size_ << custom_ << special_;

    // If this TokenItem possess a GameObject, adds its Id to the QByteArray, otherwise adds the id
    // 0 which does not correspond to any GameObject
    if (gameObject_ != NULL) {
        *stream << gameObject_->id();
    }
    else {
        int id = 0;
        *stream << id;
    }
}

GameObject *TokenItem::getGameObject() {
    return gameObject_;
}

void TokenItem::setGameObject(GameObject *gameObject) {
    gameObject_ = gameObject;
}
