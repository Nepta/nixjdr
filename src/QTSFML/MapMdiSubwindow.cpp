#include <QPoint>
#include <QImage>
#include <QMdiArea>
#include "MapMdiSubwindow.h"

const int MapMdiSubwindow::margin = 24;

MapMdiSubwindow::MapMdiSubwindow()
{
    scrollArea_ = new QScrollArea;

    setWindowTitle("Map");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint); // hide min/max buttons

    setWidget(scrollArea_);
}

MapMdiSubwindow::~MapMdiSubwindow() {
    delete scrollArea_;
}

void MapMdiSubwindow::editMapBackgroud(QString filename, bool newMap) {
    QImage bg = QImage(filename);

    // subwindow size = picture size
    int width = bg.width();
    int height = bg.height() + margin;

    // prevents subwindow from expanding outside the mdiArea
    if (mdiArea()->width() < width) {
        width = mdiArea()->width();
    }
    if (mdiArea()->height() < height) {
        height = mdiArea()->height() - margin;
    }

    resize(width, height + margin);

    // create a new map
    if (!newMap) {
        delete map_;
    }
    map_ = new Map(this, QPoint(0, margin), bg.size());
    map_->setMap(filename);
    map_->show();

    scrollArea_->setWidget(map_);

    move(0,0);
}

Map* MapMdiSubwindow::map() {
	return map_;
}
