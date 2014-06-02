#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QGraphicsObject>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QRectF>

#include "Network/ClientReceiver.h"

#include "Database/Database.h"
#include "Database/DBComponent.h"
#include "Database/DBItem.h"

/**
 * @brief The abstract Layer class is used to stack and separate different type of elements
 * from a scene.
 */
class Layer : public QGraphicsObject, public DBComponent, public DBItem
{
    Q_OBJECT

public:
    Layer() {}
    virtual ~Layer() {}

    virtual void drawBackground(QPainter *painter, const QRectF &rect) = 0;

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    void setEnabled(bool enabled);
    void setClientReceiver(ClientReceiver *clientReceiver);

protected:
    ClientReceiver *m_ClientReceiver;

    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
};

#endif // LAYER_H
