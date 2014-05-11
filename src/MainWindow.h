#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "ChatWidget.h"
#include "TokenMenu.h"
#include "DiceMenu.h"
#include "ui_TokenMenu.h"
#include "ui_DiceMenu.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const bool ROLE_MJ = true;
    static const bool ROLE_PLAYER = false;

    explicit MainWindow(bool role, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateMenu();
    void on_actionCreateMap_triggered();
    void on_actionEditMap_triggered();

signals:
    void initMainWindow();
    void sendMessageToChatUi(const QString &msg);

private:
    void setupMJ();
    void setupPlayer();

    Ui::MainWindow *ui;
    bool m_role;
    DiceMenu *m_diceMenu;
};

#endif // MAINWINDOW_H
