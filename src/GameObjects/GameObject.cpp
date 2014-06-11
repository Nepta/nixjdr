#include "GameObject.h"

GameObject::GameObject(QString name, GameObjectType type) {
    m_Name = name;
    m_Type = type;
}

GameObject::GameObject(DBItem item) {
    columnsValues_ = item.getHashMap();

    int id = columnsValues_.value("id").toInt();
    QString name = columnsValues_.value("name").toString();
    GameObjectType type = (GameObjectType) columnsValues_.value("type").toInt();

    id_ = id;
    m_Name = name;
    m_Type = type;
}

GameObject::~GameObject() {}

QString GameObject::getName() {
    return m_Name;
}

GameObjectType GameObject::getType() {
    return m_Type;
}

GameObject *GameObject::clone() {
    GameObject *clone = new GameObject(m_Name, m_Type);

    return clone;
}
