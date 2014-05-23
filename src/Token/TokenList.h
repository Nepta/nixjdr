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
    void appendCustomItem(QIcon icon, QString name);

private:
    void dragMoveEvent(QDragMoveEvent * event);
    void mousePressEvent(QMouseEvent * event);
};

#endif // TOKENLIST_H
