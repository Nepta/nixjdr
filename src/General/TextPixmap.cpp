#include <QFont>
#include <QPainter>
#include "TextPixmap.h"

TextPixmap::TextPixmap(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{}

TextPixmap::~TextPixmap() {}

/**
 * @brief TextPixmap::paintOnPixmap Paints a text on this object pixmap.
 */
void TextPixmap::paintOnPixmap() {
    QPainterPath textPath;
    QString values = QString("%1").arg(m_Text);
    textPath.addText(QPoint(0,13), QFont("Arial", 13,  QFont::Bold), values); // TODO modify QPoint (translate?)

    QPixmap pix(textPath.boundingRect().size().toSize());
    pix.fill(Qt::transparent);
    QPainter painter(&pix);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPath(textPath);

    setPixmap(pix);
}

/**
 * @brief TextPixmap::setPosCenterItem Center this object relative to the specified item position.
 */
void TextPixmap::setPosCenterItem(QGraphicsItem *item) {
    if (item != NULL) {
        setPos(item->pos());

        QRectF rect(pos(), boundingRect().size());
        QPointF spriteCenter = item->pos() + item->boundingRect().center();
        rect.moveCenter(spriteCenter);

        setPos(rect.x(), rect.y());
    }
}

void TextPixmap::setText(QString text) {
    m_Text = text;
    paintOnPixmap();
}
