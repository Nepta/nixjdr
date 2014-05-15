#include "Receiver.h"

Receiver::Receiver(QHash<QString, User *> *usersList) {
    m_UsersList = usersList;
}
