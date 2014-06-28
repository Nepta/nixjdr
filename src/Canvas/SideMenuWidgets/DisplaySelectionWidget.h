#ifndef DISPLAYSELECTIONWIDGET_H
#define DISPLAYSELECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class DisplaySelectionWidget;
}

class DisplaySelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplaySelectionWidget(QWidget *parent = 0);
    ~DisplaySelectionWidget();

    Ui::DisplaySelectionWidget *getUi();

private:
    Ui::DisplaySelectionWidget *ui;
};

#endif // DISPLAYSELECTIONWIDGET_H
