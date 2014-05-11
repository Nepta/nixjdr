#ifndef MAPMDISUBWINDOW_H
#define MAPMDISUBWINDOW_H

#include <QMdiSubWindow>
#include <QScrollArea>
#include "Map.h"

class MapMdiSubwindow : public QMdiSubWindow {
    Q_OBJECT

    public:
        explicit MapMdiSubwindow();
        ~MapMdiSubwindow();
        Map* map();
        void editMapBackgroud(QString filename, bool newMap);

    private:
        static const int margin;
        Map *map_;
        QScrollArea *scrollArea_;
};

#endif // MAPMDISUBWINDOW_H
