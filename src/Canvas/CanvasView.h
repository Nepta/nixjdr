#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QWidget>
#include <QGraphicsView>

class CanvasView : public QGraphicsView {

public:
    CanvasView(QWidget *parent = 0);
    ~CanvasView();
};

#endif // CANVASVIEW_H
