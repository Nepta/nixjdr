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

#include "Tooltip.h"
#include "CanvasView.h"
#include "CanvasScene.h"

namespace Ui {
    class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    static const int BG_OFFSET = 2*4;

    explicit Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent = 0);
    ~Map();


    Ui::Map *getUi();
    MapLayer *getMapLayer();

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
