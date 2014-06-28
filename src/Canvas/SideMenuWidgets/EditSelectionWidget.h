#ifndef EDITSELECTIONWIDGET_H
#define EDITSELECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class EditSelectionWidget;
}

class EditSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditSelectionWidget(QWidget *parent = 0);
    ~EditSelectionWidget();

    Ui::EditSelectionWidget *getUi();

private:
    Ui::EditSelectionWidget *ui;
};

#endif // EDITSELECTIONWIDGET_H
