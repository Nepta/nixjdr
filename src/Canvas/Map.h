#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QAbstractButton>
#include "Layers/BackgroundLayer.h"
#include "Layers/MapLayer.h"
#include "Layers/FoWLayer.h"
#include "Layers/DrawingLayer.h"
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

    void initTooltip();
    void initFoWLayer(int tileStep);
    void initDrawingLayer(Layer *layer);
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
    Tooltip m_MapTooltip;
    BackgroundLayer m_BgLayer;
    MapLayer m_MapLayer;
    Layer *m_FoWLayer;
    DrawingLayer m_DrawingLayer;
    bool m_IsGridFoWLayer;
    Layer *m_SelectedLayer;

    void showMapTooltip(QString tooltip);
    void hideAllToolBoxes();
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
};

#endif // MAP_H
