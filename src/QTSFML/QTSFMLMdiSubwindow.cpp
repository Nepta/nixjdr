#include <QMouseEvent>
#include <QMoveEvent>
#include <QPoint>
#include "QTSFMLMdiSubwindow.h"

QTSFMLMdiSubwindow::QTSFMLMdiSubwindow(QString filename, int height, int width, int margin)
{
    setGeometry(10, 10, width, height + margin);
    setWindowTitle("Qt SFML");

    //On crée une vue SFML dans la fenêtre principale
    map_ = new Map(this, QPoint(0, margin), QSize(width, height));
    map_->setMap(filename);
    map_->show();
}

void QTSFMLMdiSubwindow::mousePressEvent(QMouseEvent *event) {
    QMdiSubWindow::mousePressEvent(event);

    //map_->setUpdatesEnabled(false);
    map_->hide();
}

void QTSFMLMdiSubwindow::mouseReleaseEvent(QMouseEvent* event) {
    //map_->setUpdatesEnabled(true);
    map_->show();
}
