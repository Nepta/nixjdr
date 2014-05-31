#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QGraphicsObject>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QRectF>
#include "Database/Database.h"
#include "Database/DBComponent.h"

/**
 * @brief The abstract Layer class is used to stack and separate different type of elements
 * from a scene.
 */
class Layer : public QGraphicsObject, public DBComponent
{
    Q_OBJECT

public:
    Layer();
    Layer(Database *db);
    virtual ~Layer() {}

    virtual void drawBackground(QPainter *painter, const QRectF &rect) = 0;

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    void setEnabled(bool enabled);
};

#endif // LAYER_H
