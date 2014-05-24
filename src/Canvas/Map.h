#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QAbstractButton>
#include "CanvasView.h"
#include "CanvasScene.h"
#include "BackgroundLayer.h"
#include "MapLayer.h"
#include "FoWLayer.h"
#include "DrawingLayer.h"

namespace Ui {
    class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QString bgFilename, QString tokenPath, int tileStep, QWidget *parent = 0);
    ~Map();

    Ui::Map *getUi();
    MapLayer *getMapLayer();

private slots:
    void selectedEditionLayer(QAbstractButton *button, bool checked);
    void selectedDisplayLayer(QAbstractButton *button, bool checked);
    void on_collapseButton_clicked(bool checked);

private:
    Ui::Map *ui;
    BackgroundLayer m_BgLayer;
    MapLayer m_MapLayer;
    FoWLayer m_FoWLayer;
    DrawingLayer m_DrawingLayer;
};

#endif // MAP_H
