#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include "Network/Serializable/Serializable.h"
#include "Database/DBItem.h"

class AbstractAction : public Serializable
{
public:
    virtual ~AbstractAction() {}

    virtual void executeClient() = 0;
    virtual void executeServer() = 0;

    virtual QByteArray serialize();

protected:
    virtual void unserialize(QByteArray& data);

private:
    DBItem m_DBItem;
};

#endif // ABSTRACTACTION_H
