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
#include "Chat/ChatWidget.h"
#include "DiceMenu/DiceMenu.h"
#include "Canvas/MapCreationWidget.h"
#include "NotificationStacker.h"

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
    void openMap(Map *map, bool notify = false);

//Map functions
    void on_actionCreateMap_triggered();
    void on_actionCreateImage_triggered();
    void on_actionOpenMap_triggered();

//Main menu functions
    void on_actionConnection_triggered();

//Ui functions
    void on_collapseButtonRightMenu_clicked(bool checked);
    void on_collapseButtonTurnMenu_clicked();

//User creation functions
    void addPlayerToInterface(QString playerNickname);

signals:
    void initMainWindow();
    void sendMessageToChatUi(const QString &msg);

private:
    void setupMJ();
    void setupPlayer();

// inits
    void initDiceMenu();
    void initConnects();
    void initRole();
    void initTableTurnSplitter();
	void initLogger();

//Ui functions
    void collapseMenu(bool checked, QWidget *widget, QSplitter *splitter, int min, int max);

//Map functions
    void openMapCreationWidget(bool isImage);
    void createMap(QString path, int bgWidth, int bgHeight, QString mapName, int mapStep, bool isImage = false);

    Ui::MainWindow *ui;
    User *m_User;
    SwitchServer *m_Server;
    SwitchClient *m_Client;
    TurnMenu *m_turnMenu;
    QString m_FilePath ;
    NotificationStacker m_NotificationStacker;
    GameObject *m_PlayerGameObject;
};

#endif // MAINWINDOW_H
