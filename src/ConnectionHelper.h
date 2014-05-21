#ifndef CONNECTIONHELPER_H
#define CONNECTIONHELPER_H

#include <QDialog>
#include <QCloseEvent>
#include "User.h"

namespace Ui {
    class ConnectionHelper;
}

/**
 * @brief The ConnectionHelper class provides a dialog allowing the user to choose a role, the server
 * and his nickname.
 */
class ConnectionHelper : public QDialog
{
	Q_OBJECT

public:
    explicit ConnectionHelper(User *user, QWidget *parent = 0);
    ~ConnectionHelper();

public slots:
    void on_playerButton_clicked();
    void on_mjButton_clicked();
    void on_endButton_clicked();

private:
    /**
     * @brief closeEvent Prevents the User from closing the window (ignore the event)
     * @param event
     */
    void closeEvent(QCloseEvent * event);
    void keyPressEvent(QKeyEvent * event);

    Ui::ConnectionHelper *ui;
    User *m_User;
};

#endif // CONNECTIONHELPER_H
