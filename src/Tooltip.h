#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QWidget>
#include <QStack>
#include <QString>

namespace Ui {
    class Tooltip;
}

class Tooltip : public QWidget
{
    Q_OBJECT

public:
    static const int TOOLTIP_OFFSET = 20;

    explicit Tooltip(QWidget *parent = 0);
    ~Tooltip();
    void showTooltip(QPoint position);

private slots:
    void hideTooltip();
    void pushInfo(QString info);

private:
    Ui::Tooltip *ui;
    QStack<QString> m_InfoStack;

    void setTooltipText(QString text);
};

#endif // TOOLTIP_H
