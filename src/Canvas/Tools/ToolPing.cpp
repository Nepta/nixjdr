#include "ToolPing.h"

ToolPing::ToolPing(QGraphicsScene *scene, QString gifPath):
    m_Scene(scene),
    m_GifPath(gifPath)
{
    m_Gif = new QLabel();
    m_Movie = new QMovie("resource/gifs/ping/pingSuwako.gif");
}

ToolPing::~ToolPing(){
    delete m_Gif;
    delete m_Movie;
}

void ToolPing::setSize(int size){}

void ToolPing::ping(QPointF pos){
    m_Gif->setMovie(m_Movie);
    m_Movie->start();
//    QGraphicsProxyWidget *proxy = m_Scene->addWidget(m_Gif);
}

bool ToolPing::sceneEventFilter(QGraphicsItem *, QEvent *event){
    bool eventFiltered = false;
    switch (event->type()) {
        case  QEvent::GraphicsSceneMousePress:{
            pressMouse(static_cast<QGraphicsSceneMouseEvent*>(event));
            eventFiltered = true;
            event->accept();
        }
            break;
        default:
            break;
    }
    AbstractTool::updateDisplay();
    return eventFiltered;
}


void ToolPing::pressMouse(QGraphicsSceneMouseEvent *mouseEvent){
    if(mouseEvent->button() == Qt::LeftButton){
        ping(mouseEvent->pos());
    }
}
