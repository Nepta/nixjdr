#include <QObject>

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
    // If CircularProgressBar is not correctly initialized, do not paint it
    if (m_MaxValue == 0) {
        return;
    }

    QGraphicsPixmapItem::paint(painter, option, widget);
    painter->setRenderHint(QPainter::Antialiasing);

    // Outer ellipse
    painter->setPen(QPen(QBrush(Qt::black), 5));
    painter->drawEllipse(boundingRect().center(), m_Radius, m_Radius);

    // Inner ellipse
    painter->setPen(QPen(QBrush(Qt::red), 2));
    int startAngle = 90 * 16;
    int endAngle = (FULL_CIRCLE/m_MaxValue) * m_Value;
    painter->drawArc(boundingRect(), startAngle, endAngle);

    // text value/maxValue
    QPainterPath textPath;
    QString values = QObject::tr("%1/%2").arg(m_Value).arg(m_MaxValue);
    textPath.addText(QPoint(0,0), QFont("Arial", 13,  QFont::Bold), values);
    QRectF rect = textPath.boundingRect();
    rect.moveCenter(boundingRect().center());
    textPath.translate(rect.x(), rect.y());
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawPath(textPath);
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
