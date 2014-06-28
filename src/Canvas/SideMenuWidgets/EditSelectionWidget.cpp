#include "EditSelectionWidget.h"
#include "ui_EditSelectionWidget.h"

EditSelectionWidget::EditSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditSelectionWidget)
{
    ui->setupUi(this);
}

EditSelectionWidget::~EditSelectionWidget()
{
    delete ui;
}

Ui::EditSelectionWidget *EditSelectionWidget::getUi(){
    return ui;
}
