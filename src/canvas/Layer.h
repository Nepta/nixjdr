#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Layer : public QGraphicsObject
{
    Q_OBJECT

public:
    Layer() {}
    virtual ~Layer() {}

    virtual void drawBackground(QPainter *painter, const QRectF &rect) = 0;

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif // LAYER_H
