#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QWidget>
#include <QGraphicsView>

class CanvasView : public QGraphicsView {

    Q_OBJECT

public:
    CanvasView(QWidget *parent = 0);
    ~CanvasView();

private:
    double m_ScaleFactor;

private slots:
    void zoom(int value);

signals:
    void changeLabelScale(double);
};

#endif // CANVASVIEW_H
