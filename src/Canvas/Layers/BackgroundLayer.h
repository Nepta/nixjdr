#ifndef BACKGROUNDLAYER_H
#define BACKGROUNDLAYER_H

#include "AbstractLayer.h"

/**
 * @brief The BackgroundLayer class represents a layer with a centered background
 */
class BackgroundLayer : public AbstractLayer
{
public:
    BackgroundLayer(QString filename);
    BackgroundLayer(DBItem item);
    ~BackgroundLayer();

    /**
     * @brief drawBackground draws m_Background at the center of the scene (if m_Background is
     * smaller than the scene, the zone around the pixmap is painted in white).
     * @param painter
     * @param rect
     */
    void drawBackground(QPainter *painter, const QRectF &rect);

    QPixmap* getBackground();
    QByteArray getBackgroundData();

private:
    QPixmap m_Background;
};

#endif // BACKGROUNDLAYER_H
