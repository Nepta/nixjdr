#ifndef NOTIFICATIONSTACKER_H
#define NOTIFICATIONSTACKER_H

#include <QList>
#include <QTimer>

#include "Tooltip.h"

class NotificationStacker : public QObject
{
public:
    NotificationStacker();

private:
    QList<Tooltip> *m_Stack;

    void timerEvent(QTimerEvent *event);
};

#endif // NOTIFICATIONSTACKER_H
