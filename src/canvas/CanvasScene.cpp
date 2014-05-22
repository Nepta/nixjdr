#include "CanvasScene.h"

#include <QDebug>


#define LAYER_MAX 4

CanvasScene::CanvasScene() : DBItem("map")
{
    this->setSceneRect(0, 0, 800, 600);
    m_spritePath = "resource/sakuya.png";
}


CanvasScene::CanvasScene(QString filename, int step) : DBItem("Map")
{
	 m_step = step;
	 pushDB(filename);
	 pushDB(step);
    m_spritePath = "resource/sakuya.png";
    m_background = new QPixmap(filename);
    const int width = m_background->width();
    const int height = m_background->height();

    initMatrix(width, height);

    if(m_step != 1) {
        drawGrid(width, height);
    }

    this->setSceneRect(0, 0, width, height);
    this->setBackgroundBrush(*m_background);
}

CanvasScene::~CanvasScene()
{
    delete m_background;
}



CanvasScene *CanvasScene::getCanvasScene()
{
    return this;
}


void CanvasScene::addSprite(QPixmap *sprite, int x, int y)
{
    QGraphicsPixmapItem* item;
    int z = 1;

    int xTab = x/m_step;
    int yTab = y/m_step;

    int xTile = xTab*m_step;
    int yTile = yTab*m_step;

    item = m_spriteMatrix[yTab][xTab][z];

    z = indexOfUpperItem(xTab, yTab)+1;
    if(z < LAYER_MAX){
        item = this->addPixmap(*sprite);
        item->setPos(xTile, yTile);
        item->setZValue(z);
        m_spriteMatrix[yTab][xTab][z] = item;
    }

    if(z == LAYER_MAX){
        qDebug() << "layer max dépassé";
    }
}


void CanvasScene::removeSprite(int x, int y)
{
    int xTab = x/m_step;
    int yTab = y/m_step;

    int z = indexOfUpperItem(xTab, yTab);

    if(z != 0){
        QGraphicsItem* item;
        item = m_spriteMatrix[yTab][xTab][z];
        this->removeItem(item);
    }

    m_spriteMatrix[yTab][xTab][z] = NULL;
}

void CanvasScene::initMatrix(int width, int height)
{
    for(int i = 0; i < height/m_step; i++){
        QList<QList<QGraphicsPixmapItem*>> listHeight;
        m_spriteMatrix.append(listHeight);
        for(int j = 0; j < width/m_step; j++){
            QList<QGraphicsPixmapItem*> listWidth;
            m_spriteMatrix[i].append(listWidth);
            for(int k = 0; k < LAYER_MAX; k++){
                m_spriteMatrix[i][j].append(NULL);
            }
        }
    }
}


void CanvasScene::drawGrid(int width, int height)
{
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

QGraphicsPixmapItem *CanvasScene::getPixmapItem(int x, int y)
{
    int xTab = x/m_step;
    int yTab = y/m_step;

    int z = indexOfUpperItem(xTab, yTab);
    return m_spriteMatrix[yTab][xTab][z];
}

QString CanvasScene::getSpritePath()
{
    return m_spritePath;
}

int CanvasScene::indexOfUpperItem(int x, int y)
{
    int z = 0;

    for(z = LAYER_MAX-1; z > 0; z--){
        if(m_spriteMatrix[y][x][z] != NULL){
            break;
        }
    }

    return z;
}

void CanvasScene::setSpritePath(QListWidgetItem *sprite)
{
    QString newPath = QString("resource/%1.png").arg(sprite->text());
    m_spritePath = newPath;
}
