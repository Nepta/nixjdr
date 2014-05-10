#include <QMouseEvent>
#include <QMoveEvent>
#include <QPoint>
#include <QImage>
#include <QScrollArea>
#include "MapMdiSubwindow.h"
#include "ui_MapMdiSubwindow.h"

MapMdiSubwindow::MapMdiSubwindow(QString filename)
{
    QImage bg = QImage(filename);
    QScrollArea *sa = new QScrollArea;

    int margin = 24;

    setWindowTitle("Map");
    resize(bg.width(), bg.height() + margin);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint); // hide min/max buttons

    map_ = new Map(this, QPoint(0, margin), bg.size());
    map_->setMap(filename);
    map_->show();

    sa->setWidget(map_);
    setWidget(sa);
}

MapMdiSubwindow::~MapMdiSubwindow() {
}

Map* MapMdiSubwindow::map() {
	return map_;
}
