#include <QMouseEvent>
#include <QMoveEvent>
#include <QPoint>
#include "MapMdiSubwindow.h"

MapMdiSubwindow::MapMdiSubwindow(QString filename, int height, int width, int margin)
{
    setGeometry(10, 10, width, height + margin);
    setWindowTitle("Qt SFML");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint); // hide min/max buttons

    //On crée une vue SFML dans la fenêtre principale
    map_ = new Map(this, QPoint(0, margin), QSize(width, height));
    map_->setMap(filename);
    map_->show();
}

Map* MapMdiSubwindow::map() {
	return map_;
}
