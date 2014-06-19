#ifndef NOTIFICATIONSTACKER_H
#define NOTIFICATIONSTACKER_H

#include <QList>
#include <QTimer>

#include "Tooltip.h"

#define TIMER_INTERVAL 3500

class NotificationStacker : public QObject
{
    Q_OBJECT

public:
    NotificationStacker();
    ~NotificationStacker();

    void setParent(QWidget* parent);

public slots:
    void pushNotification(QString text);

private:
    QList<Tooltip*> m_Stack;
    int m_Timer;
    int m_Size;
    QWidget* m_Parent;
    Tooltip* m_LastNotif;

    void timerEvent(QTimerEvent *event);
    void updatePosition();
};

#endif // NOTIFICATIONSTACKER_H
