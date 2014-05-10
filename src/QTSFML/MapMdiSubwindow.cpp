#include <QMouseEvent>
#include <QMoveEvent>
#include <QPoint>
#include <QImage>
#include "MapMdiSubwindow.h"

MapMdiSubwindow::MapMdiSubwindow(QString filename)
{
    int margin = 24;
    QImage bg = QImage(filename);

    setGeometry(10, 10, bg.width(), bg.height() + margin);
    setWindowTitle("Map");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint); // hide min/max buttons

    map_ = new Map(this, QPoint(0, margin), bg.size());
    map_->setMap(filename);
    map_->show();
}

Map* MapMdiSubwindow::map() {
	return map_;
}
