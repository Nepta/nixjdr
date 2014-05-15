#include "canvas.h"

#include <QDebug>

Canvas::Canvas()
{
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 800, 600);

    m_view = new QGraphicsView(m_scene);

}

Canvas::Canvas(QString filename, int step) {

    m_step = step;
    m_background = new QPixmap(filename);
    const int width = m_background->width();
    const int height = m_background->height();

    for(int i = 0; i < height/step; i++){
        QList<QGraphicsItem*> list;
        m_SpriteMatrix.append(list);
        for(int j = 0; j < width/step; j++){
            m_SpriteMatrix[i].append(NULL);
        }
    }

    if(m_step != 1) {
        drawGrid(width, height);
    }

    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, width, height);

    m_view = new QGraphicsView(m_scene);


    m_scene->setBackgroundBrush(*m_background);
    m_view->ensureVisible ( m_scene->sceneRect() );

    m_canvasEventHandler = new CanvasEventHandler();
    this->m_view->installEventFilter(m_canvasEventHandler);
    connect(m_canvasEventHandler, SIGNAL(addSprite(QPixmap*, int, int, int)),
                        this, SLOT(addSprite(QPixmap*, int, int, int)));
    connect(m_canvasEventHandler, SIGNAL(removeSprite(int, int, int)),
                        this, SLOT(removeSprite(int, int, int)));
}



QGraphicsScene* Canvas::getScene() {
    return m_scene;
}

QGraphicsView* Canvas::getView() {
    return m_view;
}

CanvasEventHandler* Canvas::getCanvasEventHandler(){
    return m_canvasEventHandler;
}

void Canvas::drawGrid(int width, int height){
    QPainter painter;
//    painter.setPen(Qt::white,1,Qt::DashLine);
    painter.begin(m_background);

    for(int i = 0; i < width; i+=m_step){
        painter.drawLine(i, 0, i, height);
    }

    for(int i = 0; i < height; i+=m_step){
        painter.drawLine(0, i, width, i);
    }

    painter.end();
}

void Canvas::addSprite(QPixmap* sprite, int x, int y, int z){

    QGraphicsItem* item;

    int xTab = x/m_step;
    int yTab = y/m_step;

    int xTile = xTab*m_step;
    int yTile = yTab*m_step;

    if(m_SpriteMatrix[yTab][xTab] == NULL){
        item = m_scene->addPixmap(*sprite);
        item->setPos(xTile, yTile);
        item->setZValue(z);

        m_SpriteMatrix[yTab][xTab] = item;
    }
}

void Canvas::removeSprite(int x, int y, int z){
    int xTab = x/m_step;
    int yTab = y/m_step;

    qDebug() << "remove Sprite";

    QGraphicsItem* item;
    item = m_SpriteMatrix[yTab][xTab];
    m_scene->removeItem(item);

    m_SpriteMatrix[yTab][xTab] = NULL;
}
