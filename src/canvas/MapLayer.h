#ifndef MAPLAYER_H
#define MAPLAYER_H

#include <QListWidgetItem>
#include <QPainter>
#include "Layer.h"

class MapLayer : public Layer
{
    Q_OBJECT

public:
    static const int START_DRAG_DISTANCE = 4;

    MapLayer(QString tokenPath, int step = 1);
    ~MapLayer();

    void setTokenPath(QString tokenPath);
    void addSprite(QPoint position);
    void addSprite(QPixmap *pixmap, QPoint position);
    void removeSprite(QGraphicsItem *sprite);

    void drawBackground(QPainter *painter, const QRectF &rect);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    /**
     * @brief mousePressEvent Reimplemented from Layer in order to grab mouse events
     * @param mouseEvent
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);

public slots:
    void setTokenPath(QListWidgetItem* token);

private:
    int m_Step;
    QString m_SpritePath;
    QPoint m_dragStartPosition;

    void initDragEvent(QGraphicsItem *watched, QGraphicsSceneMouseEvent *mouseEvent);

};

#endif // MAPLAYER_H
