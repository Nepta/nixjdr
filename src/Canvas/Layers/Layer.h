#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRectF>

/**
 * @brief The abstract Layer class is used to stack and separate different type of elements
 * from a scene.
 */
class Layer : public QGraphicsObject
{
    Q_OBJECT

public:
    Layer() {}
    virtual ~Layer() {}

    virtual void drawBackground(QPainter *painter, const QRectF &rect) = 0;

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    void setEnabled(bool enabled);

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
};

#endif // LAYER_H
