#include "Sprite.h"

Sprite::Sprite(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent) {}

Sprite::Sprite(QByteArray& data) {
    unserialize(data);
}

Sprite::~Sprite() {
}

void Sprite::setTransparent(bool enabled) {
    if (enabled) {
        setOpacity(0.75);
    } else {
        setOpacity(1.0);
    }
}

// Reimplemented from Serializable

QByteArray Sprite::serialize() {
    // TODO pixmap, x, y, in which scene (should be identified with a unique id)
}

void Sprite::unserialize(QByteArray& data) {
    // TODO retrieve pixmap, x ,y, which scene
}
