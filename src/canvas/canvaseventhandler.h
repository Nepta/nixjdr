#ifndef CANVASEVENTHANDLER_H
#define CANVASEVENTHANDLER_H

#include <QEvent>
#include <QPixmap>
#include <QObject>
#include <QListWidgetItem>

class CanvasEventHandler : public QObject
{
    Q_OBJECT

signals:
    void addSprite(QPixmap* sprite, int x, int y, bool isMoving);
    void removeSprite(int x, int y);

public:
    CanvasEventHandler();
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void setSpritePath(QListWidgetItem *sprite);
    void moveSprite();

private:
    QString m_spritePath;
    bool m_isMoving;
};

#endif // CANVASEVENTHANDLER_H
