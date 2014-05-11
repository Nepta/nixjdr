#include "CustomMdiArea.h"

CustomMdiArea::CustomMdiArea(QWidget *parent) :
    QMdiArea(parent)
{
}

QMdiSubWindow *CustomMdiArea::addSubWindow(QWidget *widget, Qt::WindowFlags flags) {
    QMdiSubWindow *subwindow = QMdiArea::addSubWindow(widget, flags);

    subwindow->setOption(QMdiSubWindow::RubberBandResize, true);
    subwindow->setOption(QMdiSubWindow::RubberBandMove, true);

    return subwindow;
}
