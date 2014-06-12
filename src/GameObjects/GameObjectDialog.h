#ifndef GAMEOBJECTDIALOG_H
#define GAMEOBJECTDIALOG_H

#include <QDialog>

#include "GameObject.h"

namespace Ui {
class GameObjectDialog;
}

class GameObjectDialog : public QDialog
{
    Q_OBJECT

public:
    GameObjectDialog(QWidget *parent = 0);
    GameObjectDialog(GameObject *gameObject, QWidget *parent = 0);
    ~GameObjectDialog();

    GameObject *getGameObject();

private slots:
    void on_createButton_clicked();

private:
    Ui::GameObjectDialog *ui;
    GameObject *m_Object;
    bool m_EditMode;
};

#endif // GAMEOBJECTDIALOG_H
