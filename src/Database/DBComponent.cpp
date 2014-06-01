#include "DBComponent.h"

DBComponent::DBComponent() {}

DBComponent::DBComponent(Database *db) {
    db_ = db;
}

DBComponent::~DBComponent() {}

DBComponent *DBComponent::setDatabase(Database *db) {
    db_ = db;

    return this;
}
