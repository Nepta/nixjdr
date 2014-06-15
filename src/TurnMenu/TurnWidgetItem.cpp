#include "TurnWidgetItem.h"
#include "ui_TurnWidgetItem.h"
#include "StyleSheet.h"

TurnWidgetItem::TurnWidgetItem(QListWidgetItem *item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TurnWidgetItem)
{
    ui->setupUi(this);
    setStyleSheet(StyleSheet::s_StyleSheet);

    m_Item = item;
}

TurnWidgetItem::~TurnWidgetItem()
{
    delete ui;
}

void TurnWidgetItem::on_closeButton_clicked() {
    emit deleteTurn(m_Item);
}
