#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include "canvaseventhandler.h"

CanvasEventHandler::CanvasEventHandler()
{
    m_spritePath = "resource/suwako.png";
    m_isMoving = false;
}

bool CanvasEventHandler::eventFilter(QObject *obj, QEvent *event){
    bool eventHandled = false;
    Qt::MouseButton mouseButton;
    QPixmap* sprite = new QPixmap(m_spritePath);

    if(typeid(*obj) == typeid(QGraphicsView)){
        if(event->type()==QEvent::MouseButtonPress){
            mouseButton = static_cast<QMouseEvent*>(event)->button();
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            int x = mouseEvent->x();
            int y = mouseEvent->y();

            if(mouseButton == Qt::LeftButton) {
                emit addSprite(sprite, x, y, m_isMoving);
            }

            else if(mouseButton == Qt::RightButton) {
                emit removeSprite(x, y);
            }

            eventHandled = true;
        }
    }

//    else if(typeid(*obj) == typeid(QGraphicsScene)){
//        if(event->type()==QEvent::GraphicsSceneMouseRelease && m_isMoving == true){

//            mouseButton = static_cast<QMouseEvent*>(event)->button();
//            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
//            int x = mouseEvent->x();
//            int y = mouseEvent->y();

//            qDebug()<<m_isMoving << x << y;
//            emit addSprite(sprite, x, y, 1, m_isMoving);
//            m_isMoving = false;
//            eventHandled = true;
//        }
//    }

    else{
        return QObject::eventFilter(obj, event);
    }
    return eventHandled;
}

void CanvasEventHandler::setSpritePath(QListWidgetItem* sprite){
    QString newPath = QString("resource/%1.png").arg(sprite->text());
    m_spritePath = newPath;
}

void CanvasEventHandler::moveSprite(){
    m_isMoving = true;
}
