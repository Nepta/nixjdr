#ifndef CUSTOMMDIAREA_H
#define CUSTOMMDIAREA_H

#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>

namespace Ui {
    class CustomMdiArea;
}

/**
 * @brief CustomMdiArea class - redefines addSubWindow to add proper options for each
 * subwindow in order to avoid flickering problems.
 */
class CustomMdiArea : public QMdiArea
{
    public:
        /**
         * @brief CustomMdiArea
         */
        CustomMdiArea(QWidget *parent);
        ~CustomMdiArea();

        /**
         * @brief addSubWindow - redefines QMdiArea addSubWindow by adding the RubberBandResize
         *        and RubberBandMove options to the subwindow in order to avoid flickering problems.
         * @param widget
         * @param flags
         */
        QMdiSubWindow *addSubWindow(QWidget *widget, Qt::WindowFlags flags = 0);

    private:
        Ui::CustomMdiArea *ui;
};

#endif // CUSTOMMDIAREA_H
