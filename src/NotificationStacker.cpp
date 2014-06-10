#include "NotificationStacker.h"

#include <QDebug>

NotificationStacker::NotificationStacker(){
    this->startTimer(2000);
}

void NotificationStacker::timerEvent(QTimerEvent *event)
{
    if(m_Stack->empty() != NULL){
        m_Stack->pop_front();
    }
}
