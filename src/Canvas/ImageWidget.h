#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include "Layers/BackgroundLayer.h"
#include "Layers/DrawingLayer.h"
#include "Tooltip.h"
#include "CanvasView.h"
#include "CanvasScene.h"

namespace Ui {
    class Map;
}

class ImageWidget : public QWidget, public DBComponent
{
    Q_OBJECT

public:
    static const int BG_OFFSET = 250;
    explicit ImageWidget(QString bgFilename, QWidget *parent = 0);

public slots:
    void on_collapseButton_clicked(bool checked);

private:
    void initDrawingLayer(AbstractLayer *layer);
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

    Ui::Map *ui;
    CanvasScene *m_Scene;
    BackgroundLayer m_BgLayer;
    DrawingLayer m_DrawingLayer;
};

#endif // IMAGEWIDGET_H
