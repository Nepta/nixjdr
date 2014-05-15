#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "Network/Server.h"
#include "Network/Client.h"
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
    explicit MainWindow(User *user, QWidget *parent = 0);
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
    DiceMenu *m_diceMenu;
    User *m_User;
    Server *m_Server;
    Client *m_Client;
};

#endif // MAINWINDOW_H
