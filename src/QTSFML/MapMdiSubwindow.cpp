#include <QMouseEvent>
#include <QMoveEvent>
#include <QPoint>
#include <QImage>
#include "MapMdiSubwindow.h"

const int MapMdiSubwindow::margin = 24;

MapMdiSubwindow::MapMdiSubwindow(QString filename)
{
    scrollArea_ = new QScrollArea;

    setWindowTitle("Map");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint); // hide min/max buttons

    map_ = NULL;
    editMapBackgroud(filename);
    setWidget(scrollArea_);
}

MapMdiSubwindow::~MapMdiSubwindow() {
    delete scrollArea_;
}

void MapMdiSubwindow::editMapBackgroud(QString filename) {
    QImage bg = QImage(filename);

    resize(bg.width(), bg.height() + margin);

    delete map_;
    map_ = new Map(this, QPoint(0, margin), bg.size());
    map_->setMap(filename);
    map_->show();

    scrollArea_->setWidget(map_);
}

Map* MapMdiSubwindow::map() {
	return map_;
}
