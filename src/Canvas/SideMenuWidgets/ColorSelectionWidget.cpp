#include <QColorDialog>
#include "ColorSelectionWidget.h"
#include "ui_ColorSelectionWidget.h"

ColorSelectionWidget::ColorSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSelectionWidget)
{
    ui->setupUi(this);
}

ColorSelectionWidget::~ColorSelectionWidget()
{
    delete ui;
}

void ColorSelectionWidget::selectButtonColor(QPushButton *button){
    QColorDialog colorDlg;
    QColor color = colorDlg.getColor();
    setButtonColor(button, color);
}

void ColorSelectionWidget::setButtonColor(QPushButton *button, QColor color){
    QPalette palette = button->palette();
    palette.setColor(button->backgroundRole(), color);
    button->setAutoFillBackground(true);
    button->setPalette(palette);
    button->show();

    if(button == ui->m_FirstColorButton){
        emit(mainColorChanged(color));
    }
}

void ColorSelectionWidget::on_m_FirstColorButton_clicked()
{
    selectButtonColor(ui->m_FirstColorButton);
}

void ColorSelectionWidget::on_m_SecondColorButton_clicked()
{
    selectButtonColor(ui->m_SecondColorButton);
}

void ColorSelectionWidget::on_m_DefaultColorButton_clicked()
{
    setButtonColor(ui->m_FirstColorButton, Qt::black);
    setButtonColor(ui->m_SecondColorButton, Qt::white);
}

void ColorSelectionWidget::on_m_SwapButton_clicked()
{
    QColor oldFirstButtonColor = ui->m_FirstColorButton->palette().color(ui->m_FirstColorButton->backgroundRole());
    QColor oldSecondButtonColor = ui->m_SecondColorButton->palette().color(ui->m_SecondColorButton->backgroundRole());

    setButtonColor(ui->m_FirstColorButton, oldSecondButtonColor);
    setButtonColor(ui->m_SecondColorButton, oldFirstButtonColor);
}

QColor ColorSelectionWidget::getCurrentColor(){
    return ui->m_FirstColorButton->palette().color(ui->m_FirstColorButton->backgroundRole());
}
