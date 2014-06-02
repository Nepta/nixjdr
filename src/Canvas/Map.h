#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QAbstractButton>
#include "Layers/BackgroundLayer.h"
#include "Layers/MapLayer.h"
#include "Layers/FoWLayer.h"
#include "Layers/DrawingLayer.h"
#include "Layers/Layers.h"
#include "Layers/AbstractLayer.h"

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

    Ui::Map *getUi();
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

    void initScene();
    void initLayers();
    void initDisplay();
    void initMapTools();
    void initFoWTools();
    void initTooltip();
    void initDrawingLayer(LayerCodes code);

    void showMapTooltip(QString tooltip);
    void hideAllToolBoxes();
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
};

#endif // MAP_H
