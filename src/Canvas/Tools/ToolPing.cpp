#include "ToolPing.h"
#include <QTimeLine>

ToolPing::ToolPing(QGraphicsScene *scene, QString gifPath):
    m_Scene(scene),
    m_GifPath(gifPath)
{
    m_Gif = new QLabel();
    m_Movie = new QMovie(m_GifPath);
    m_Gif->setMovie(m_Movie);
    m_Gif->setAttribute(Qt::WA_TranslucentBackground);
    m_Proxy = m_Scene->addWidget(m_Gif);
    m_Proxy->hide();
}

ToolPing::~ToolPing(){
    delete m_Gif;
    delete m_Movie;
}

void ToolPing::setSize(int){}

void ToolPing::ping(QPointF pos){
    if(!m_Pinging){
        emit sendPing(pos);

        QRectF rect(pos, QSizeF(32, 32));
        rect.moveCenter(pos);

        m_Proxy->setGeometry(rect);
        m_Movie->start();
        m_Proxy->show();
        m_Pinging = true;
        startTimer(1000);
    }
}

void ToolPing::timerEvent(QTimerEvent *timerEvent){
    m_Proxy->hide();
    killTimer(timerEvent->timerId());
    m_Movie->stop();
    m_Pinging = false;
}

bool ToolPing::sceneEventFilter(QGraphicsItem *, QEvent *event){
    bool eventFiltered = false;
    switch (event->type()) {
        case  QEvent::GraphicsSceneMousePress:{
            pressMouse(static_cast<QGraphicsSceneMouseEvent*>(event));
            eventFiltered = true;
        }
            break;
        default:
            break;
    }
    if(eventFiltered){
        event->accept();
    }
    return eventFiltered;
}


void ToolPing::pressMouse(QGraphicsSceneMouseEvent *mouseEvent){
    if(mouseEvent->button() == Qt::LeftButton){
        ping(mouseEvent->pos());
    }
}
