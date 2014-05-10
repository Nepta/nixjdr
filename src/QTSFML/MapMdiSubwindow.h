#ifndef MAPMDISUBWINDOW_H
#define MAPMDISUBWINDOW_H

#include <QMdiSubWindow>
#include "Map.h"

class MapMdiSubwindow : public QMdiSubWindow {
    Q_OBJECT

    public:
        explicit MapMdiSubwindow(QString filename);
        ~MapMdiSubwindow();
        Map* map();

    private:
        Map *map_;
};

#endif // MAPMDISUBWINDOW_H
