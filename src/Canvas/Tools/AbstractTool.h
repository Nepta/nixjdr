#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>

enum class ToolCodes : quint16;

class AbstractTool : public QGraphicsObject
{
    Q_OBJECT

public:
    static QPixmap *getPixmap();
    static void setPixmap(QPixmap *pixmap);
    static QGraphicsPixmapItem *getDrawingZone();
    static void setDrawingZone(QGraphicsPixmapItem *drawingZone);


    AbstractTool() {}
    virtual ~AbstractTool(){}

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    virtual void setSize(int size) = 0;

protected:
    virtual void updateDisplay();

    virtual bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) =0;

private:
    static QPixmap *s_Pixmap;
    static QGraphicsPixmapItem *s_DrawingZone;

};

#endif // ABSTRACTTOOL_H
