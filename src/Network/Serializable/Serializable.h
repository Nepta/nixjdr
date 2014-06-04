#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QByteArray>

class Serializable
{
public:
    Serializable() {}
    virtual ~Serializable() {}

public:
    virtual QByteArray serialize() = 0;

protected:
    virtual void unserialize(QByteArray& data) = 0;
};

#endif // SERIALIZABLE_H
