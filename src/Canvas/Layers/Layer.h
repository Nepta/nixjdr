#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRectF>

class Layer : public QGraphicsObject
{
    Q_OBJECT

public:
    Layer() {}
    virtual ~Layer() {}

    virtual void drawBackground(QPainter *painter, const QRectF &rect) = 0;

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    /**
     * @brief setEnabled Reimplemented from QGraphicsObject. Notifies the layer that the geometry of
     * the layer will change before calling QGraphicsObject::setEnabled(). The boundingRect() depends
     * on the enabled attribute.
     * @param enabled
     */
    void setEnabled(bool enabled);
};

#endif // LAYER_H
