#include "AbstractAction.h"

QByteArray AbstractAction::serialize() {
    QByteArray serializedDBItem = m_DBItem.serialize();

    return serializedDBItem;
}

void AbstractAction::unserialize(QByteArray& data) {
    m_DBItem.unserialize(data);
}
