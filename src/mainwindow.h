#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

#include "chat/chatserver.h"
#include "chat/chatclient.h"
#include "tokenmenu.h"
#include "ui_tokenmenu.h"
#include "dicemenu.h"
#include "ui_dicemenu.h"


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
    void on_actionModify_Background_triggered();
    void on_msgField_returnPressed();
    void receivedMessage(const QString &msg);
    void updateNicknamesListView();
    void rollDice(QString);

signals:
    void initMainWindow();

private:
    void setupMJ();
    void setupPlayer();
    void setupChatServer();
    void setupChatClient();
    void sendMessageFromClientToServer(QString message);

    Ui::MainWindow *ui;
    bool m_role;
    DiceMenu *m_diceMenu;
    ChatServer *m_chatServer;
    ChatClient *m_chatClient;
    QStringListModel *m_NicknamesListModel;
};

#endif // MAINWINDOW_H
