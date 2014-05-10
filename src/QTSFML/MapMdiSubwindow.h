#ifndef MAPMDISUBWINDOW_H
#define MAPMDISUBWINDOW_H

#include <QMdiSubWindow>
#include <QScrollArea>
#include "Map.h"

class MapMdiSubwindow : public QMdiSubWindow {
    Q_OBJECT

    public:
        explicit MapMdiSubwindow(QString filename);
        ~MapMdiSubwindow();
        Map* map();
        void editMapBackgroud(QString filename);

    private:
        static const int margin;
        Map *map_;
        QScrollArea *scrollArea_;
};

#endif // MAPMDISUBWINDOW_H
