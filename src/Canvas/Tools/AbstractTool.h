#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>

enum class ToolCodes : quint16;

/**
 * @brief The AbstractTool class Reimplemented from QGraphicsObject. The boundingRect returns 0 width
 * / height so that it will not intercept mouse events occuring on the layer.
 */
class AbstractTool : public QGraphicsObject
{
    Q_OBJECT

public:
    static QPixmap *getPixmap();
    static void setPixmap(QPixmap *pixmap);

    AbstractTool() {}
    virtual ~AbstractTool(){}

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    virtual void setSize(int size) = 0;

protected:
    virtual bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) = 0;

private:
    static QPixmap *s_Pixmap;

signals:
    void updateDisplay();

};

#endif // ABSTRACTTOOL_H
