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
    QString getPath();
    void setNameToken(QString name);

private slots:
    void on_createButton_clicked();

    void on_m_SearchButton_clicked();

private:
    Ui::GameObjectDialog *ui;
    GameObject *m_Object;
    QString m_Path;
    bool m_EditMode;
};

#endif // GAMEOBJECTDIALOG_H
