#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>
#include "Network/Serializable.h"

class Sprite : public QGraphicsPixmapItem, public Serializable
{
public:
    Sprite(const QPixmap &pixmap, QGraphicsItem *parent = 0);
    Sprite(QByteArray& data);
    ~Sprite();

    QByteArray serialize();

private:
    void unserialize(QByteArray& data);

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // SPRITE_H
