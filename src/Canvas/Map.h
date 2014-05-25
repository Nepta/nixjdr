#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QAbstractButton>
#include "Layers/BackgroundLayer.h"
#include "Layers/MapLayer.h"
#include "Layers/FoWLayer.h"
#include "Layers/DrawingLayer.h"
#include "MapTooltip.h"
#include "CanvasView.h"
#include "CanvasScene.h"

namespace Ui {
    class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent = 0);
    ~Map();

    void initTooltip();
    void initDrawingLayer();
    Ui::Map *getUi();
    MapLayer *getMapLayer();

private slots:
    void selectedEditionLayer(QAbstractButton *button, bool checked);
    void selectedDisplayLayer(QAbstractButton *button, bool checked);
    void on_collapseButton_clicked(bool checked);
    void showMapTooltip(Sprite* sprite);
    void hideMapTooltip();

private:
    Ui::Map *ui;
    CanvasScene *m_Scene;
    MapTooltip m_MapTooltip;
    BackgroundLayer m_BgLayer;
    MapLayer m_MapLayer;
    FoWLayer m_FoWLayer;
    DrawingLayer m_DrawingLayer;
};

#endif // MAP_H
