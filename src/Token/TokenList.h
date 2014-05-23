#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QListWidget>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>
#include <QGraphicsPixmapItem>

class TokenList: public QListWidget
{
public:
    TokenList(QWidget * parent = 0);
    QListWidgetItem getCurrentItem();

private:
    void dragMoveEvent(QDragMoveEvent * event);
    void mousePressEvent(QMouseEvent * event);
};

#endif // TOKENLIST_H
