#ifndef QTSFMLMDISUBWINDOW_H
#define QTSFMLMDISUBWINDOW_H

#include <QMdiSubWindow>
#include "Map.h"

class QTSFMLMdiSubwindow : public QMdiSubWindow
{
public:
    QTSFMLMdiSubwindow(QString filename, int height, int width, int margin);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    Map *map_;
    bool isMoving_;
};

#endif // QTSFMLMDISUBWINDOW_H
