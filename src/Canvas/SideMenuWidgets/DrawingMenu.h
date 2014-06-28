#ifndef DRAWINGMENU_H
#define DRAWINGMENU_H

#include <QWidget>

namespace Ui {
class DrawingMenu;
}

/**
 * @brief The DrawingMenu class represents a widget containing the necessary buttons to use a
 * drawingLayer
 */
class DrawingMenu : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingMenu(QWidget *parent = 0);
    ~DrawingMenu();
    Ui::DrawingMenu *getUi();

private slots:
    void on_m_PenButton_clicked();

    void on_m_EraserButton_clicked();

    void on_m_PingButton_clicked();

private:
    Ui::DrawingMenu *ui;
};

#endif // DRAWINGMENU_H
