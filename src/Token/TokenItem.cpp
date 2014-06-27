#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QByteArray>
#include <QVariant>

#include "Database/Repository/RepositoryManager.h"
#include "Database/Repository/GameObjectRepository.h"
#include "TokenItem.h"

const QString TokenItem::DEFAULT_ICON_PATH = "resource/TokenMenu/keroro.png";

TokenItem::TokenItem(QString path, QString text, int size, bool special) :
    DBItem()
{
    gameObject_ = NULL;

    construct(path, text, size, special);
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
    QByteArray iconData = columnsValues_.value("icon").toByteArray();
    int size = columnsValues_.value("size").toInt();
    bool special = columnsValues_.value("special").toBool();

    QIcon icon;
    QDataStream stream(&iconData, QIODevice::ReadOnly);
    stream >> icon;

    // Retrieve gameObject from the database
    int gameobjectid = columnsValues_.value("gameobjectid").toInt();
    if (gameobjectid != 0) {
        gameObject_ = RepositoryManager::s_CharacterRepository.getFullGameObject(gameobjectid);
    }
    else {
        gameObject_ = NULL;
    }

    construct(id, icon, text, size, special);
}

void TokenItem::construct(QString path, QString text, int size, bool special) {
    setText(text);
    size_ = size;
    special_ = special;

    setIcon(path);
}

void TokenItem::construct(int id, QIcon icon, QString text, int size, bool special) {
    id_ = id;
    setText(text);
    size_ = size;
    special_ = special;
    QListWidgetItem::setIcon(icon);
}

void TokenItem::construct(QDataStream *stream) {
    int id, size, gameObjectId;
    QString text;
    QIcon icon;
    bool special;

    *stream >> id >> text >> icon >> size >> special >> gameObjectId;

    if (gameObjectId != 0) {
        gameObject_ = RepositoryManager::s_CharacterRepository.getFullGameObject(gameObjectId);
    }

    construct(id, icon, text, size, special);
}

/**
 * @brief setIcon Overloaded method. Sets the icon to the image specified by its path and sets
 * m_PixLoaded accordingly (true if the image was loaded successfully, false otherwise).
 * @param path
 */
void TokenItem::setIcon(QString path) {
    QPixmap pix;

    if (!pix.load(path)) {
        pix.load(DEFAULT_ICON_PATH);
        pixLoaded_ = false;
    }
    else {
        pixLoaded_ = true;
    }

    QListWidgetItem::setIcon(QIcon(pix));
}

QByteArray TokenItem::iconPixmapData() {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << icon();

    return data;
}

bool TokenItem::isPixLoaded() {
    return pixLoaded_;
}

int TokenItem::size() {
    return size_;
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
    *stream << id_ << text() << icon() << size_ << special_;

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

int TokenItem::getPixmapSize(){
    return icon().availableSizes().first().width();
}

void TokenItem::setGameObject(GameObject *gameObject) {
    gameObject_ = gameObject;
}

TokenItem *TokenItem::setSize(int size){
    size_ = size;
    return this;
}

