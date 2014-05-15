#include <QMouseEvent>

#include "canvaseventhandler.h"

CanvasEventHandler::CanvasEventHandler()
{
}

bool CanvasEventHandler::eventFilter(QObject *obj, QEvent *event){
    bool eventHandled = false;
//Qt::MouseButton mouseButton = static_cast<QMouseEvent*>(event)->button();
    if(event->type()==QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        int x = mouseEvent->x();
        int y = mouseEvent->y();
        QPixmap* cirno = new QPixmap("resource/cirno.png");
        emit addSprite(cirno, x, y, 1);
        eventHandled = true;
    }
    else{
        return QObject::eventFilter(obj, event);
    }

    return eventHandled;
}