#include <QFileDialog>

#include "MapCreationWidget.h"
#include "ui_MapCreationWidget.h"
#include "StyleSheet.h"

MapCreationWidget::MapCreationWidget(bool isImage, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapCreationWidget)
{
    ui->setupUi(this);
    setStyleSheet(StyleSheet::s_StyleSheet);

    m_IsImage = isImage;

    if (isImage) {
        ui->stepWidget->hide();
    }
}

MapCreationWidget::~MapCreationWidget()
{
    delete ui;
}

void MapCreationWidget::on_m_MapCreationButton_clicked()
{
    accept();
}

void MapCreationWidget::on_m_SearchButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", "resource",
                                                "Images (*.png *.xpm *.jpg)");
    ui->m_ImageEdit->setText(path);
}

QString MapCreationWidget::getMapName(){
    return ui->m_MapNameTextBox->text();
}

QString MapCreationWidget::getImagePath(){
    return ui->m_ImageEdit->text();
}

int MapCreationWidget::getStep(){
    return ui->m_MapStepSpinBox->value();
}

int MapCreationWidget::getBgWidht(){
    return ui->m_BgWidth->value();
}

int MapCreationWidget::getBgHeight(){
    return ui->m_BgHeight->value();
}

bool MapCreationWidget::getIsWhite(){
    return ui->m_BgIsWhite->isChecked();
}

