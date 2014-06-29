#include <QColorDialog>
#include "ColorSelectionWidget.h"
#include "ui_ColorSelectionWidget.h"

ColorSelectionWidget::ColorSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSelectionWidget)
{
    ui->setupUi(this);

    initLayout();
}

ColorSelectionWidget::~ColorSelectionWidget()
{
    delete ui;
}

/**
 * @brief ColorSelectionWidget::initLayout positions and resizes the buttons so that they look like
 * Gimp's Ui. Positioning is made based on minimum values for the display buttons and the widget
 * itself
 */
void ColorSelectionWidget::initLayout(){
    int firstWidth = ui->m_FirstColorButton->minimumWidth();
    int firstHeight = ui->m_FirstColorButton->minimumHeight();
    int secondWidth = ui->m_SecondColorButton->minimumWidth();
    int secondHeight = ui->m_SecondColorButton->minimumHeight();

    ui->m_FirstColorButton->setGeometry(0,0,firstWidth,firstHeight);
    ui->m_SecondColorButton->setGeometry(width()-secondWidth,height()-secondHeight,secondWidth,secondHeight);
    ui->m_DefaultColorButton->setGeometry(0,firstHeight,width()-secondWidth,height()-firstHeight);
    ui->m_SwapButton->setGeometry(firstWidth,0,width()-firstWidth,height()-secondHeight);
}

/**
 * @brief ColorSelectionWidget::selectButtonColor opens a dialog window and changes the button's
 * background to the chosen color
 * @param button
 */
void ColorSelectionWidget::selectButtonColor(QPushButton *button){
    QColorDialog colorDlg;
    QColor color = colorDlg.getColor();
    setButtonColor(button, color);
}

/**
 * @brief ColorSelectionWidget::setButtonColor sets the specified button's background to the given
 * color
 * @param button
 * @param color
 */
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

/**
 * @brief ColorSelectionWidget::setDefaultColors resets the display button's colors to black & white
 */
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

/**
 * @brief ColorSelectionWidget::on_m_SwapButton_clicked swaps the display button's color
 */
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
