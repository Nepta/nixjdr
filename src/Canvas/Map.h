#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QAbstractButton>
#include "Layers/BackgroundLayer.h"
#include "Layers/MapLayer.h"
#include "Layers/FoWLayer.h"
#include "Layers/DrawingLayer.h"
#include "Database/DBItem.h"
#include "MapTooltip.h"
#include "CanvasView.h"
#include "CanvasScene.h"

namespace Ui {
    class Map;
}

class Map : public QWidget, public DBItem
{
    Q_OBJECT

public:
    explicit Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent = 0);
    // TODO Map(DBItem item);
    ~Map();

    void construct(int id, QString bgFilename, QString tokenPath, int tileStep);
    void construct(QString bgFilename, QString tokenPath, int tileStep);

    void initTooltip();
    void initBgLayer(QString bgFilename);
    void initMapLayer(QString tokenPath, int tileStep);
    void initFoWLayer(int tileStep);
    void initDrawingLayer();
    void initDrawingLayer(Layer *layer);
    void initScene(int tileStep);

    Ui::Map *getUi();
    MapLayer *getMapLayer();

private slots:
    void selectedEditionLayer(QAbstractButton *button, bool checked);
    void selectedDisplayLayer(QAbstractButton *button, bool checked);
    void on_collapseButton_clicked(bool checked);
    void hideMapTooltip();
    void showMapMoveTooltip(int oldPosX, int oldPosY, int CurrentPosX, int CurrentPosY);
    void showMapSpriteTooltip(Sprite* sprite);

private:
    Ui::Map *ui;
    CanvasScene m_Scene;
    MapTooltip m_MapTooltip;
    BackgroundLayer *m_BgLayer;
    MapLayer *m_MapLayer;
    Layer *m_FoWLayer;
    DrawingLayer *m_DrawingLayer;
    bool m_IsGridFoWLayer;

    void showMapTooltip(QString tooltip);
    void hideAllToolBoxes();
};

#endif // MAP_H
