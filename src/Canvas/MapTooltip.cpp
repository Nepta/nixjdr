#include "MapTooltip.h"
#include "ui_MapTooltip.h"

MapTooltip::MapTooltip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapTooltip)
{
    ui->setupUi(this);
}

MapTooltip::~MapTooltip()
{
    delete ui;
}

void MapTooltip::setTooltipText(QString text) {
    ui->m_TooltipText->setText(text);
    adjustSize();
}
