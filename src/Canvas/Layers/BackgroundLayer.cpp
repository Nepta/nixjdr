#include "BackgroundLayer.h"

#include <QByteArray>
#include <QBuffer>

BackgroundLayer::BackgroundLayer(QString filename) :
    m_Background(filename)
{}

BackgroundLayer::~BackgroundLayer() {}

void BackgroundLayer::drawBackground(QPainter *painter, const QRectF &rect) {
    QRect targetRect = m_Background.rect();
    targetRect.moveCenter(rect.center().toPoint());

    painter->drawPixmap(targetRect, m_Background, m_Background.rect());
}

QPixmap *BackgroundLayer::getBackground() {
    return &m_Background;
}

QByteArray BackgroundLayer::getBackgroundData() {
    QByteArray bg;
    QBuffer buffer(&bg);
    buffer.open(QIODevice::WriteOnly);
    m_Background.save(&buffer, "PNG");

    return bg;
}
