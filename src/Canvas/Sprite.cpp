#include "Sprite.h"

#include <QDebug>

Sprite::Sprite(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent) {}

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
