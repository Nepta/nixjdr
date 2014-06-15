#include "CustomMdiArea.h"
#include "ui_CustomMdiArea.h"

CustomMdiArea::CustomMdiArea(QWidget *parent) :
    QMdiArea(parent),
    ui(new Ui::CustomMdiArea)
{
    ui->setupUi(this);
}

CustomMdiArea::~CustomMdiArea() {
    delete ui;
}

QMdiSubWindow *CustomMdiArea::addSubWindow(QWidget *widget, Qt::WindowFlags flags) {
    QMdiSubWindow *subwindow = QMdiArea::addSubWindow(widget, flags);

    subwindow->setWindowIcon(QIcon(""));
    subwindow->setOption(QMdiSubWindow::RubberBandResize, true);
    subwindow->setOption(QMdiSubWindow::RubberBandMove, true);

    return subwindow;
}
