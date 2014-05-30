#include "DrawingMenu.h"
#include "ui_DrawingMenu.h"

DrawingMenu::DrawingMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawingMenu)
{
    ui->setupUi(this);
}

DrawingMenu::~DrawingMenu()
{
    delete ui;
}

Ui::DrawingMenu *DrawingMenu::getUi() {
    return ui;
}
