#include <QFont>
#include <QPainter>
#include "TextPixmap.h"

const int TextPixmap::FONT_POINT_SIZE = 14;
const int TextPixmap::FONT_PIX_SIZE = 20;
const int TextPixmap::WIDTH_PADDING = 8;
const QPoint TextPixmap::FONT_BASELINE(0, 14);
const QPointF TextPixmap::SPRITE_OFFSET(0, 4);

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

    // Prepares the text path which will be painted on the pixmap. WIDTH_PADDING is added because
    // QPainterPath does not seem to give enough space to fit all the text.
    QFont font("Arial", FONT_POINT_SIZE, QFont::Bold);
    font.setStyleStrategy(QFont::ForceOutline);
    textPath.addText(FONT_BASELINE + QPoint(WIDTH_PADDING/2, 0), font, values);

    // Paints the text with a border on the pixmap.
    QPixmap pix(textPath.boundingRect().size().width() + WIDTH_PADDING, FONT_PIX_SIZE);
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
 * @param offset Offset to add after the TextPixmap has been centered.
 */
void TextPixmap::setPosCenterItem(QGraphicsItem *item, QPointF offset) {
    if (item != NULL) {
        setPos(item->pos());

        QRectF rect(pos(), boundingRect().size());
        QPointF spriteCenter = item->pos() + item->boundingRect().center();
        rect.moveCenter(spriteCenter);
        rect.translate(offset);

        setPos(rect.x(), rect.y());
    }
}

void TextPixmap::setText(QString text) {
    m_Text = text;
    paintOnPixmap();
}
