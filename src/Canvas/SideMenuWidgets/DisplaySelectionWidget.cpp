#include "DisplaySelectionWidget.h"
#include "ui_DisplaySelectionWidget.h"

DisplaySelectionWidget::DisplaySelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplaySelectionWidget)
{
    ui->setupUi(this);
}

DisplaySelectionWidget::~DisplaySelectionWidget()
{
    delete ui;
}

Ui::DisplaySelectionWidget *DisplaySelectionWidget::getUi(){
    return ui;
}
