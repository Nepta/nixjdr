#ifndef MAPCREATIONWIDGET_H
#define MAPCREATIONWIDGET_H

#include <QDialog>

namespace Ui {
class MapCreationWidget;
}

class MapCreationWidget : public QDialog
{
    Q_OBJECT

public:
    explicit MapCreationWidget(QWidget *parent = 0);
    ~MapCreationWidget();

signals:
    void createMap(QString mapName, int mapStepValue);

private slots:
    void on_m_MapCreationButton_clicked();

private:
    Ui::MapCreationWidget *ui;
};

#endif // MAPCREATIONWIDGET_H
