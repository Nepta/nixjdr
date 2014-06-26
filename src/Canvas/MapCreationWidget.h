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
    explicit MapCreationWidget(bool isMap, QWidget *parent = 0);
    ~MapCreationWidget();

    QString getMapName();
    QString getImagePath();
    int getStep();
    int getBgWidht();
    int getBgHeight();
    bool getIsWhite();

private slots:
    void on_m_MapCreationButton_clicked();

    void on_m_SearchButton_clicked();

private:
    Ui::MapCreationWidget *ui;
    bool m_IsMap;
};

#endif // MAPCREATIONWIDGET_H
