#ifndef MAPMDISUBWINDOW_H
#define MAPMDISUBWINDOW_H

#include <QMdiSubWindow>
#include "Map.h"

class MapMdiSubwindow : public QMdiSubWindow {
    public:
        MapMdiSubwindow(QString filename, int height, int width, int margin);
        Map* map();

    private:
        Map *map_;
};

#endif // MAPMDISUBWINDOW_H
