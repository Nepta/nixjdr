#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QAbstractButton>

#include "Network/MapClient.h"
#include "Network/MapServer.h"
#include "Layers/BackgroundLayer.h"
#include "Layers/MapLayer.h"
#include "Layers/FoWLayer.h"
#include "Layers/DrawingLayer.h"

#include "Database/DBComponent.h"
#include "Database/DBItem.h"

#include "Tooltip.h"
#include "CanvasView.h"
#include "CanvasScene.h"

namespace Ui {
    class Map;
}

class Map : public QWidget, public DBItem, public DBComponent
{
    Q_OBJECT

public:
    static const int BG_OFFSET = 2*4;

    explicit Map(QString bgFilename, TokenItem *tokenItem, int tileStep, QWidget *parent = 0);
    // TODO Map(DBItem item);
    ~Map();

    void construct(int id, QString bgFilename, TokenItem *tokenItem, int tileStep);
    void construct(QString bgFilename, TokenItem *tokenItem, int tileStep);

    void setupMapClient(MapClient *mapClient);
    void setupMapServer(MapServer *mapServer);

    void initTooltip();
    void initBgLayer(QString bgFilename);
    void initMapLayer(TokenItem *tokenItem, int tileStep);
    void initFoWLayer(int tileStep);
    void initDrawingLayer();
    void initDrawingLayer(Layer *layer);
    void initScene(int tileStep);

    Ui::Map *getUi();
    int getSceneHeight();
    int getSceneWidth();
    BackgroundLayer *getBgLayer();
    MapLayer *getMapLayer();
    Layer *getFoWLayer();
    DrawingLayer *getDrawingLayer();


private slots:
    void selectedEditionLayer(QAbstractButton *button, bool checked);
    void selectedDisplayLayer(QAbstractButton *button, bool checked);
    void on_collapseButton_clicked(bool checked);
    void showMapTooltip();

private:
    Ui::Map *ui;

    MapClient *m_MapClient;
    MapServer *m_MapServer;

    CanvasScene m_Scene;
    Tooltip m_Tooltip;
    bool m_IsGridFoWLayer;
    Layer *m_SelectedLayer;

    BackgroundLayer *m_BgLayer;
    MapLayer *m_MapLayer;
    Layer *m_FoWLayer;
    DrawingLayer *m_DrawingLayer;

    void showMapTooltip(QString tooltip);
    void hideAllToolBoxes();
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
};

#endif // MAP_H
