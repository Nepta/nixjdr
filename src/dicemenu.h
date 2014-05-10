#ifndef DICEMENU_H
#define DICEMENU_H

#include <QWidget>

namespace Ui {
class DiceMenu;
}

class DiceMenu : public QWidget
{
    Q_OBJECT

public:
    explicit DiceMenu(QWidget *parent = 0);
    ~DiceMenu();
/*
protected:
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
*/

private slots:
    void on_diceFourButton_clicked();
    void on_diceSixButton_clicked();
    void on_diceEightButton_clicked();
    void on_diceTenButton_clicked();
    void on_diceTwelveButton_clicked();
    void on_diceSixteenButton_clicked();
    void on_diceTwentyButton_clicked();
    void on_publicRollButton_clicked();
    void on_privateRollButton_clicked();
signals:
    void rollDice(QString);

private:
    void addDiceToRoll(int diceType);
    Ui::DiceMenu *ui;
    QString m_dicesToRoll;
//    QPoint m_oldPos;
};

#endif // DICEMENU_H
