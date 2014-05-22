#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "Canvas/Map.h"
#include "Network/Server.h"
#include "Network/Client.h"
#include "ChatWidget.h"
#include "token/TokenMenu.h"
#include "DiceMenu.h"
#include "ui_TokenMenu.h"
#include "ui_DiceMenu.h"
#include "DataBase/DataBase.h"


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

signals:
    void initMainWindow();
    void sendMessageToChatUi(const QString &msg);

private:
    void setupMJ();
    void setupPlayer();
    void createMap(QString filename);

    Ui::MainWindow *ui;
    DiceMenu *m_diceMenu;
    User *m_User;
    Server *m_Server;
	 Client *m_Client;
	 DataBase *m_db;
};

#endif // MAINWINDOW_H
