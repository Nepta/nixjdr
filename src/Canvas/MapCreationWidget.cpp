#include "MapCreationWidget.h"
#include "ui_MapCreationWidget.h"
#include "StyleSheet.h"

MapCreationWidget::MapCreationWidget(bool image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapCreationWidget)
{
    ui->setupUi(this);
    setStyleSheet(StyleSheet::s_StyleSheet);

    m_IsImage = image;
}

MapCreationWidget::~MapCreationWidget()
{
    delete ui;
}

void MapCreationWidget::on_m_MapCreationButton_clicked()
{
    emit createMap(ui->m_MapNameTextBox->text(), ui->m_MapStepSpinBox->value(), m_IsImage);
    this->close();
}
