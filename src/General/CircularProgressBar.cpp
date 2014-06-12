#include "CircularProgressBar.h"

CircularProgressBar::CircularProgressBar(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    m_Radius = 0;
    m_MinValue = 0;
    m_MaxValue = 0;
    m_Value = 0;

    m_Pixmap = NULL;
    updatePixmap();
}

CircularProgressBar::~CircularProgressBar() {}

/**
 * @brief CircularProgressBar::paint Reimplemented from QGraphicsPixmapItem. Draw a circular
 * progress bar.
 * @param painter
 * @param option
 * @param widget
 */
void CircularProgressBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
    QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);
    painter->setPen(QPen(QBrush(Qt::black), 1));

    painter->drawEllipse(boundingRect().center(), m_Radius, m_Radius);
}

void CircularProgressBar::setPos(const QPointF &pos) {
    QPointF newPos(
        pos.x() - m_Radius/2,
        pos.y() - m_Radius/2
    );

    QGraphicsPixmapItem::setPos(newPos);
}

void CircularProgressBar::setValue(int value) {
    m_Value = value;
}

void CircularProgressBar::setMaxValue(int maxValue) {
    m_MaxValue = maxValue;
}

void CircularProgressBar::setRadius(int radius) {
    m_Radius = radius;

    updatePixmap();
}

void CircularProgressBar::updatePixmap() {
    delete m_Pixmap;
    m_Pixmap = new QPixmap(m_Radius*2, m_Radius*2);
    m_Pixmap->fill(Qt::transparent);
    setPixmap(*m_Pixmap);
}
