#include "BackgroundLayer.h"

#include <QByteArray>
#include <QBuffer>

BackgroundLayer::BackgroundLayer(QString filename) :
    m_Background(filename)
{}

BackgroundLayer::BackgroundLayer(DBItem item) {
    QHash<QString, QVariant> itemHashMap = item.getHashMap();
    columnsValues_ = item.getHashMap();

    int id = itemHashMap.value("id").toInt();
    QByteArray pixmap = itemHashMap.value("pixmap").toByteArray();

    id_ = id;
    m_Background.loadFromData(pixmap, "PNG");
}

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
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    m_Background.save(&buffer, "PNG");

    return data;
}
