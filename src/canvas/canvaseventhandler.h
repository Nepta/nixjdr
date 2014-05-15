#ifndef CANVASEVENTHANDLER_H
#define CANVASEVENTHANDLER_H

#include <QEvent>
#include <QPixmap>
#include <QObject>

class CanvasEventHandler : public QObject
{
    Q_OBJECT

signals:
    void addSprite(QPixmap* sprite, int x, int y, int z);

public:
    CanvasEventHandler();
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // CANVASEVENTHANDLER_H