#ifndef OPENMAPWIDGET_H
#define OPENMAPWIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class OpenMapWidget;
}

class OpenMapWidget : public QDialog
{
    Q_OBJECT

public:
    explicit OpenMapWidget(int *mapId, QWidget *parent = 0);
    ~OpenMapWidget();

private slots:
    void on_openButton_clicked();

private:
    Ui::OpenMapWidget *ui;
    int *m_MapId;
};

#endif // OPENMAPWIDGET_H
