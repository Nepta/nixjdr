#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include <QPainter>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include "DataBase/DBItem.h"

class CanvasScene : public QGraphicsScene, public DBItem{
    Q_OBJECT

public:
    CanvasScene();
    CanvasScene(QString filename, int step=1);
    ~CanvasScene();
    CanvasScene* getCanvasScene();
    QGraphicsPixmapItem* getPixmapItem(int x, int y);
    QString getSpritePath();
    void addSprite(QPixmap* sprite, int x, int y);
    void removeSprite(int x, int y);

private:
    void initMatrix(int width, int height);
    void drawGrid(int width, int height);
    int indexOfUpperItem(int x, int y);

private:
    int m_step;
    QPixmap* m_background;
    QList<QList<QList<QGraphicsPixmapItem*>>> m_spriteMatrix;
    QString m_spritePath;

public slots:
    void setSpritePath(QListWidgetItem* sprite);

};

#endif // CANVASSCENE_H
