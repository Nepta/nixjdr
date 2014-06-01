#include "DBComponent.h"

DBComponent::DBComponent() {}

DBComponent::DBComponent(Database *db) {
    db_ = db;
    setRepositoryManager(db->getRepositoryManager());
}

DBComponent::~DBComponent() {}

DBComponent *DBComponent::setDatabase(Database *db) {
    db_ = db;
    setRepositoryManager(db->getRepositoryManager());

    return this;
}

DBComponent *DBComponent::setRepositoryManager(RepositoryManager *rm) {
    rm_ = rm;

    return this;
}
