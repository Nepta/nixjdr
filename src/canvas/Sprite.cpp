#include "Sprite.h"

#include <QDebug>

Sprite::Sprite(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{
    setAcceptDrops(true);
}

Sprite::Sprite(QByteArray& data) {
    unserialize(data);
}

Sprite::~Sprite() {
}

// Reimplemented from Serializable

QByteArray Sprite::serialize() {
    // TODO pixmap, x, y, in which scene (should be identified with a unique id)
}

void Sprite::unserialize(QByteArray& data) {
    // TODO retrieve pixmap, x ,y, which scene
}

// Reimplemented from QGraphicsPixmapItems

void Sprite::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    // TODO
    qDebug() << __FILE__ << "dragEnterEvent";
}

void Sprite::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    // TODO
    qDebug() << __FILE__ << "dragLeaveEvent";
}

void Sprite::dropEvent(QGraphicsSceneDragDropEvent *event) {
    // TODO
    qDebug() << __FILE__ << "dropEvent";
}
