#ifndef TURNWIDGETITEM_H
#define TURNWIDGETITEM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QString>

namespace Ui {
class TurnWidgetItem;
}

class TurnWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit TurnWidgetItem(QListWidgetItem *item, QWidget *parent = 0);
    ~TurnWidgetItem();

private slots:
    void on_closeButton_clicked();

private:
    Ui::TurnWidgetItem *ui;
    QListWidgetItem *m_Item;

signals:
    void deleteTurn(QListWidgetItem *item);
};

#endif // TURNWIDGETITEM_H
