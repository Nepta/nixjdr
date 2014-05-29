#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QSplitter>

#include "Canvas/Map.h"
#include "Network/Server.h"
#include "Network/Client.h"
#include "ChatWidget.h"
#include "Token/TokenMenu.h"
#include "TurnMenu/TurnMenu.h"
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
    void on_actionConnection_triggered();

    void on_collapseButtonRightMenu_clicked(bool checked);


    void on_collapseButtonTurnMenu_clicked(bool checked);

signals:
    void initMainWindow();
    void sendMessageToChatUi(const QString &msg);

private:
    void setupMJ();
    void setupPlayer();
    void createMap(QString filename);
    //init
    void initDiceMenu();
    void initConnects();
    void initRole();
    void initTableTurnSplitter();


    void collapseMenu(bool checked, QWidget *widget, QSplitter *splitter, int min, int max);

    Ui::MainWindow *ui;
    User *m_User;
    Server *m_Server;
    Client *m_Client;
    TurnMenu *m_turnMenu;
};

#endif // MAINWINDOW_H
