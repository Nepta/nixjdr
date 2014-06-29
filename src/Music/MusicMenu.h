#ifndef MUSICMENU_H
#define MUSICMENU_H

#include <QWidget>

namespace Ui {
class MusicMenu;
}

class MusicMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MusicMenu(QWidget *parent = 0);
    ~MusicMenu();

private:
    Ui::MusicMenu *ui;
};

#endif // MUSICMENU_H
