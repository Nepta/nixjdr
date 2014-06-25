#ifndef TEXTPIXMAP_H
#define TEXTPIXMAP_H

#include <QGraphicsPixmapItem>

class TextPixmap : public QGraphicsPixmapItem
{
public:
    static const int FONT_POINT_SIZE;
    static const int FONT_PIX_SIZE;
    static const int WIDTH_PADDING;
    static const QPoint FONT_BASELINE;
    static const QPointF SPRITE_OFFSET;

    TextPixmap(QGraphicsItem *parent = 0);
    ~TextPixmap();

    void setPosCenterItem(QGraphicsItem *item, QPointF offset = QPointF(0,0));
    void setText(QString text);

private:
    void paintOnPixmap();

    QString m_Text;
};

#endif // TEXTPIXMAP_H
