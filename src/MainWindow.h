#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QSplitter>

#include "Network/SwitchServer.h"
#include "Network/SwitchClient.h"
#include "TurnMenu/TurnMenu.h"
#include "Token/TokenMenu.h"
#include "Canvas/Map.h"

#include "Database/DBComponent.h"

#include "ChatWidget.h"
#include "DiceMenu.h"
#include "ui_TokenMenu.h"
#include "ui_DiceMenu.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public DBComponent
{
    Q_OBJECT

public:
    explicit MainWindow(User *user, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openMap(Map *map);
    void updateMenu();
    void on_actionCreateMap_triggered();
    void on_actionCreateImage_triggered();
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
    void createImage(QString filename);

    // inits
    void initDBComponents();
    void initDiceMenu();
    void initConnects();
    void initRole();
    void initTableTurnSplitter();


    void collapseMenu(bool checked, QWidget *widget, QSplitter *splitter, int min, int max);

    Ui::MainWindow *ui;
    User *m_User;
    SwitchServer *m_Server;
    SwitchClient *m_Client;
    TurnMenu *m_turnMenu;
};

#endif // MAINWINDOW_H
