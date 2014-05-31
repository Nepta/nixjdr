#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(QString filename) :
    m_Background(filename)
{}

BackgroundLayer::~BackgroundLayer() {}

void BackgroundLayer::drawBackground(QPainter *painter, const QRectF &rect) {
    QRect targetRect = m_Background.rect();
    targetRect.moveCenter(rect.center().toPoint());

    painter->drawPixmap(targetRect, m_Background, m_Background.rect());
}

QPixmap *BackgroundLayer::getBackground()
{
    return &m_Background;
}
