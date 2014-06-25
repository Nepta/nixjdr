#ifndef TEXTPIXMAP_H
#define TEXTPIXMAP_H

#include <QGraphicsPixmapItem>

class TextPixmap : public QGraphicsPixmapItem
{
public:
    TextPixmap(QGraphicsItem *parent = 0);
    ~TextPixmap();

    void paintOnPixmap();
    void setPosCenterItem(QGraphicsItem *item);
    void setText(QString text);

private:
    QString m_Text;
};

#endif // TEXTPIXMAP_H
