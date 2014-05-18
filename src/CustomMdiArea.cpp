#include "CustomMdiArea.h"

CustomMdiArea::CustomMdiArea(QWidget *parent) :
    QMdiArea(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

QMdiSubWindow *CustomMdiArea::addSubWindow(QWidget *widget, Qt::WindowFlags flags) {
    QMdiSubWindow *subwindow = QMdiArea::addSubWindow(widget, flags);

    subwindow->setOption(QMdiSubWindow::RubberBandResize, true);
    subwindow->setOption(QMdiSubWindow::RubberBandMove, true);

    return subwindow;
}
