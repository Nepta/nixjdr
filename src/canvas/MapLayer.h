#ifndef MAPLAYER_H
#define MAPLAYER_H

#include <QListWidgetItem>
#include <QPainter>
#include "Layer.h"

class MapLayer : public Layer
{
    Q_OBJECT

public:
    MapLayer(QString tokenPath, int step = 1);
    ~MapLayer();

    void setTokenPath(QString tokenPath);
    void addSprite(QPoint position);
    void removeSprite(QGraphicsItem *sprite);

    void drawBackground(QPainter *painter, const QRectF &rect);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:
    void setTokenPath(QListWidgetItem* token);

private:
    int m_Step;
    QString m_SpritePath;

};

#endif // MAPLAYER_H
