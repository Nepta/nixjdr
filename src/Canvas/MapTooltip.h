#ifndef MAPTOOLTIP_H
#define MAPTOOLTIP_H

#include <QWidget>

namespace Ui {
    class MapTooltip;
}

class MapTooltip : public QWidget
{
    Q_OBJECT

public:
    static const int MAP_TOOLTIP_OFFSET = 20;

    explicit MapTooltip(QWidget *parent = 0);
    ~MapTooltip();

    void setTooltipText(QString text);

private:
    Ui::MapTooltip *ui;
};

#endif // MAPTOOLTIP_H
