#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QAbstractButton>

#include "Network/SenderHandler.h"

#include "Layers/BackgroundLayer.h"
#include "Layers/MapLayer.h"
#include "Layers/FoWLayer.h"
#include "Layers/DrawingLayer.h"
#include "Layers/Layers.h"
#include "Layers/AbstractLayer.h"

#include "Database/DBItem.h"

#include "Tooltip.h"
#include "CanvasView.h"
#include "CanvasScene.h"
#include "NotificationStacker.h"

namespace Ui {
    class Map;
}

class Map : public QWidget, public DBItem, public SenderHandler
{
    Q_OBJECT

public:
    static const int BG_OFFSET = 2*4;

    explicit Map(QString mapName, QString bgFilename, TokenItem *tokenItem, int tileStep, QWidget *parent = 0);
    Map(DBItem item, BackgroundLayer *bgLayer, MapLayer *mapLayer, FoWLayer *fowLayer,
        DrawingLayer *drawingLayer);
    ~Map();

    void closeEvent(QCloseEvent *closeEvent);

    void setSenderClient(SenderClient *senderClient);

    int getSceneHeight();
    int getSceneWidth();
    BackgroundLayer *getBgLayer();
    MapLayer *getMapLayer();
    FoWLayer *getFoWLayer();
    DrawingLayer *getDrawingLayer();

private slots:
    void selectedEditionLayer(QAbstractButton *button, bool checked);
    void selectedDisplayLayer(QAbstractButton *button, bool checked);
    void on_collapseButton_clicked(bool checked);
    void showMapTooltip();

private:
    Ui::Map *ui;
    CanvasScene *m_Scene;
    Tooltip m_Tooltip;
    AbstractLayer *m_SelectedLayer;
    Layers *m_Layers;
    QHash<LayerCodes, QWidget *> m_EditionMap;

    void initScene(int tileStep);
    void initScene(int sceneWidth, int sceneHeight);
    void initDisplay();
    void initTooltip();

    void initLayers(bool addToDb = true);
    void initMapTools();
    void initFoWTools();
    void initDrawingTools();
    void initBgLayer(bool addToDb);
    void initMapLayer(bool addToDb);
    void initFoWLayer(bool addToDb);
    void initDrawingLayer(bool addToDb);

    void showMapTooltip(QString tooltip);
    void hideAllToolBoxes();
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
};

#endif // MAP_H
