#ifndef DICEMENU_H
#define DICEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QWheelEvent>

namespace Ui {
    class DiceMenu;
}

class DiceMenu : public QWidget
{
    Q_OBJECT

public:
    explicit DiceMenu(QWidget *parent = 0);
    ~DiceMenu();

private slots:
    void on_publicRollButton_clicked();
    void on_privateRollButton_clicked();
    void on_cancelButton_clicked();
    void modifyButton(QPushButton *buttonToModidy, bool actionToExecute);
    void requestRoll(QString &msg);

signals:
    void rollDice(QString, bool);
    void rightClickDiceButton(QPushButton *buttonToModify, bool actionToExecute);
    void sendMessageToChatUi(QString);

private:
    Ui::DiceMenu *ui;
    QList<QPushButton*> m_DiceButtonList;

    QString diceToRoll();
    bool eventFilter(QObject *obj, QEvent *ev);
    void fillDiceButtonList();
};

#endif // DICEMENU_H