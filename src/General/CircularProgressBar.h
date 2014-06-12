#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class CircularProgressBar : public QGraphicsPixmapItem
{
public:
    CircularProgressBar(QGraphicsItem *parent = 0);
    ~CircularProgressBar();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setValue(int value);
    void setMaxValue(int maxValue);
    void setRadius(int radius);
    void setPos(const QPointF &pos);
    void updatePixmap();

private:
    QPixmap *m_Pixmap;
    int m_Radius;
    int m_MinValue;
    int m_MaxValue;
    int m_Value;
};

#endif // CIRCULARPROGRESSBAR_H
