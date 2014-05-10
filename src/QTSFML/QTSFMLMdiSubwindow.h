#ifndef QTSFMLMDISUBWINDOW_H
#define QTSFMLMDISUBWINDOW_H

#include <QMdiSubWindow>
#include "Map.h"

class QTSFMLMdiSubwindow : public QMdiSubWindow {
    public:
        QTSFMLMdiSubwindow(QString filename, int height, int width, int margin);
        Map* map();

    private:
        Map *map_;
};

#endif // QTSFMLMDISUBWINDOW_H
