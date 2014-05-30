#include "DBComponent.h"

DBComponent::DBComponent() {}

DBComponent::DBComponent(Database *db) {
    db_ = db;
}

DBComponent::~DBComponent() {}

void DBComponent::setDatabase(Database *db) {
    db_ = db;
}
