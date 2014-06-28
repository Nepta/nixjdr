#ifndef COLORSELECTIONWIDGET_H
#define COLORSELECTIONWIDGET_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ColorSelectionWidget;
}

class ColorSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSelectionWidget(QWidget *parent = 0);
    ~ColorSelectionWidget();
    QColor getCurrentColor();

private:
    void selectButtonColor(QPushButton *Button);
    void setButtonColor(QPushButton *Button, QColor color);

signals:
    void mainColorChanged(QColor color);

private slots:
    void on_m_FirstColorButton_clicked();
    void on_m_SecondColorButton_clicked();
    void on_m_DefaultColorButton_clicked();
    void on_m_SwapButton_clicked();

private:
    Ui::ColorSelectionWidget *ui;
};

#endif // COLORSELECTIONWIDGET_H
