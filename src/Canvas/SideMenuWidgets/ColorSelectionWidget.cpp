#include <QColorDialog>
#include "ColorSelectionWidget.h"
#include "ui_ColorSelectionWidget.h"

ColorSelectionWidget::ColorSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSelectionWidget)
{
    ui->setupUi(this);

    int firstWidth = ui->m_FirstColorButton->minimumWidth();
    int firstHeight = ui->m_FirstColorButton->minimumHeight();
    int secondWidth = ui->m_SecondColorButton->minimumWidth();
    int secondHeight = ui->m_SecondColorButton->minimumHeight();

    ui->m_FirstColorButton->setGeometry(0,0,firstWidth,firstHeight);
    ui->m_SecondColorButton->setGeometry(width()-secondWidth,height()-secondHeight,secondWidth,secondHeight);
    ui->m_DefaultColorButton->setGeometry(0,firstHeight,width()-secondWidth,height()-firstHeight);
    ui->m_SwapButton->setGeometry(firstWidth,0,width()-firstWidth,height()-secondHeight);
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

void ColorSelectionWidget::setDefaultColors(){
    setButtonColor(ui->m_FirstColorButton, Qt::black);
    setButtonColor(ui->m_SecondColorButton, Qt::white);
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
    setDefaultColors();
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
