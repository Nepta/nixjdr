#ifndef GRIDLAYER_H
#define GRIDLAYER_H

#include <QPainter>
#include <QRectF>
#include <QString>
#include <QListWidgetItem>
#include "Token/TokenItem.h"
#include "Canvas/Sprite.h"
#include "LayerType.h"
#include "AbstractLayer.h"

/**
 * @brief The GridLayer class represents a Grid on which sprites can be positionned and removed.
 */
class GridLayer : public AbstractLayer
{
    Q_OBJECT

public:
    /**
     * @brief DELTA_DELETE_SPRITE The event called to delete a Sprite is valid if the cursor does not
     * cover a distance superior to this constant.
     */
    static const int DELTA_DELETE_SPRITE = 40;

    GridLayer(int step = 1);
    virtual ~GridLayer() {}


    virtual Sprite *addSpriteToLayer(Sprite* sprite);
    Sprite *addSpriteToLayer(Sprite* sprite, QPoint position);
    Sprite *addSpriteToLayer(TokenItem *tokenItem, QPoint position, int zValue);
    virtual int addSprite(TokenItem *tokenItem, QPoint position, int zValue = 1, bool notify = true);
    int addSprite(Sprite *sprite, QPoint position);
    int addSpriteRemoteDb(Sprite *sprite);
    void addSpriteRemoteClients(Sprite *sprite);

    virtual void removeSprite(Sprite *sprite, bool localDelete = true);
    void removeSpriteById(int id);
    void removeAllSprites();

    void updateSprite(Sprite *sprite);

    void drawBackground(QPainter *painter, const QRectF &rect);

    int getStep();

public slots:
    void setTokenItem(QListWidgetItem* token);

protected:
    /**
     * @brief m_Step Cell's side size
     */
    int m_Step;

    /**
     * @brief m_TokenItem Currently selected tokenItem, used to add new sprites.
     */
    TokenItem *m_TokenItem;

    /**
     * @brief m_ActiveMouseMoveEvent true when mouseMoveEvent() is called, false when
     * mouseReleaseEvent() occurs.
     */
    bool m_ActiveMouseMoveEvent;

    LayerType m_LayerType;

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched);

private:
    QPointF m_LastRemovedSpritePoint;
    void drawRows(QPainter *painter, int rowLength, int limit, bool orientation);
    bool isInScene(QGraphicsSceneMouseEvent *mouseEvent);

signals:
	 void spriteAdded(QString);
	 void spriteRemoved(QString);
};


#endif // GRIDLAYER_H
