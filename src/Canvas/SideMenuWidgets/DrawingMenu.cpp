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

void DrawingMenu::on_m_PenButton_clicked()
{
    ui->m_OptionWidget->setCurrentWidget(ui->m_PenPage);
}

void DrawingMenu::on_m_EraserButton_clicked()
{
    ui->m_OptionWidget->setCurrentWidget(ui->m_EraserPage);
}

void DrawingMenu::on_m_PingButton_clicked()
{
    ui->m_OptionWidget->setCurrentWidget(ui->m_PingPage);
}
