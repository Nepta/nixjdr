#include "MapCreationWidget.h"
#include "ui_MapCreationWidget.h"

MapCreationWidget::MapCreationWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapCreationWidget)
{
    ui->setupUi(this);

}

MapCreationWidget::~MapCreationWidget()
{
    delete ui;
}

void MapCreationWidget::on_m_MapCreationButton_clicked()
{
    emit createMap(ui->m_MapNameTextBox->text(), ui->m_MapStepSpinBox->value());
    this->close();
}
