#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QListWidget>
#include <QPoint>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>
#include <QGraphicsPixmapItem>
#include "TokenItem.h"

class TokenList: public QListWidget
{
public:

    /**
     * @brief START_DRAG_DISTANCE Distance to cover in order to start a drag event.
     */
    static const int START_DRAG_DISTANCE = 40;

    TokenList(QWidget * parent = 0);
    QListWidgetItem getCurrentItem();
    void appendCustomItem(QIcon icon, QString name);
	 void appendCustomItem(TokenItem& item);

private:
    void dragMoveEvent(QDragMoveEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    QPoint m_dragStartPosition;
};

#endif // TOKENLIST_H
