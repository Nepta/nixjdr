#include <QKeyEvent>
#include "AbstractTool.h"

QPixmap *AbstractTool::s_Pixmap = NULL;

QRectF AbstractTool::boundingRect() const {
    return QRectF(0, 0, 0, 0);
}

void AbstractTool::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}

void AbstractTool::setPixmap(QPixmap *pixmap){
    AbstractTool::s_Pixmap = pixmap;
}

QPixmap *AbstractTool::getPixmap(){
    return AbstractTool::s_Pixmap;
}
