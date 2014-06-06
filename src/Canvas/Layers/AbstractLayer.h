#ifndef ABSTRACTLAYER_H
#define ABSTRACTLAYER_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRectF>

#include "Network/SenderClient.h"

#include "Database/Database.h"
#include "Database/DBComponent.h"
#include "Database/DBItem.h"
#include <QHash>

enum class LayerCodes : quint16;

/**
 * @brief The abstract Layer class is used to stack and separate different type of elements
 * from a scene.
 */
class AbstractLayer : public QGraphicsObject, public DBComponent, public DBItem
{
    Q_OBJECT

public:
    AbstractLayer() {}
    virtual ~AbstractLayer() {}

    virtual void drawBackground(QPainter *painter, const QRectF &rect) = 0;

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    void setEnabled(bool enabled);
    void setSenderClient(SenderClient *senderClient);

protected:
    SenderClient *m_SenderClient;

    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
};

#endif // ABSTRACTLAYER_H
