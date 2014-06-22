#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QModelIndexList>

#include "Database/Repository/RepositoryManager.h"
#include "Database/Repository/MapRepository.h"
#include "StyleSheet.h"
#include "OpenMapWidget.h"
#include "ui_OpenMapWidget.h"

OpenMapWidget::OpenMapWidget(int *mapId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenMapWidget)
{
    ui->setupUi(this);
    setStyleSheet(StyleSheet::s_StyleSheet);

    m_MapId = mapId;

    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database());
    model->setTable("map");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(1, Qt::Horizontal, tr("Nom carte"));

    QTableView *tableView = ui->m_MapTableView;
    tableView->setModel(model);

    // Hide all columns except the windowtitle (Nom) column
    for (int i = 0 ; i < model->columnCount() ; i++) {
        tableView->hideColumn(i);
    }
    tableView->showColumn(1);

    // Disable the open button if no map has been saved in the Database
    if (model->rowCount() == 0) {
        ui->openButton->setEnabled(false);
    }
    else { // Select the first row by default
        tableView->selectRow(0);
    }
}

OpenMapWidget::~OpenMapWidget()
{
    delete ui;
}

/**
 * @brief OpenMapWidget::on_openButton_clicked when the openButton is clicked, creates a map with
 * the selected options
 */
void OpenMapWidget::on_openButton_clicked()
{
    QModelIndexList selectedIndexes = ui->m_MapTableView->selectionModel()->selectedIndexes();

    if (!selectedIndexes.empty()) {
        QModelIndex modelIndex = selectedIndexes.at(0);
        *m_MapId = modelIndex.data().toInt();

        this->close();
    }
}
