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
    explicit MapCreationWidget(bool image, QWidget *parent = 0);
    ~MapCreationWidget();

signals:
    void createMap(QString mapName, int mapStepValue, bool isImage);

private slots:
    void on_m_MapCreationButton_clicked();

private:
    Ui::MapCreationWidget *ui;
    bool m_IsImage;
};

#endif // MAPCREATIONWIDGET_H
