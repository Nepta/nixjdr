#include <QKeyEvent>
#include "AbstractTool.h"

QPixmap *AbstractTool::s_Pixmap = NULL;
QGraphicsPixmapItem *AbstractTool::s_DrawingZone = NULL;

QRectF AbstractTool::boundingRect() const{
    return QRectF(0, 0, 0, 0);
}

void AbstractTool::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *){}

void AbstractTool::setPixmap(QPixmap *pixmap){
    AbstractTool::s_Pixmap = pixmap;
}

QPixmap *AbstractTool::getPixmap(){
    return AbstractTool::s_Pixmap;
}

void AbstractTool::setDrawingZone(QGraphicsPixmapItem *drawingZone){
    AbstractTool::s_DrawingZone = drawingZone;
}

QGraphicsPixmapItem *AbstractTool::getDrawingZone(){
    return AbstractTool::s_DrawingZone;
}

void AbstractTool::updateDisplay(){
    AbstractTool::s_DrawingZone->setPixmap(*AbstractTool::s_Pixmap); // update the drawing zone
}

