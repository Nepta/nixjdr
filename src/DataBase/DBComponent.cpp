#include "DBComponent.h"

DBComponent::DBComponent() {}

DBComponent::DBComponent(DataBase *db) {
    db_ = db;
}

DBComponent::~DBComponent() {}

void DBComponent::setDatabase(DataBase *db) {
    db_ = db;
}
