#include <QMouseEvent>

#include "canvaseventhandler.h"

CanvasEventHandler::CanvasEventHandler()
{
    m_spritePath = "resource/suwako.png";
}

bool CanvasEventHandler::eventFilter(QObject *obj, QEvent *event){
    bool eventHandled = false;
//Qt::MouseButton mouseButton = static_cast<QMouseEvent*>(event)->button();
    if(event->type()==QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        int x = mouseEvent->x();
        int y = mouseEvent->y();
        QPixmap* sprite = new QPixmap(m_spritePath);
        emit addSprite(sprite, x, y, 1);
        eventHandled = true;
    }
    else{
        return QObject::eventFilter(obj, event);
    }

    return eventHandled;
}

void CanvasEventHandler::setSpritePath(QListWidgetItem* sprite){
    QString newPath = QString("resource/%1").arg(sprite->text())+QString(".png");
    m_spritePath = newPath;
}
