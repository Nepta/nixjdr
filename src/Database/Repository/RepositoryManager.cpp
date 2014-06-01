#include "Database/Repository/MapRepository.h"
#include "Database/Repository/SpriteRepository.h"
#include "Database/Repository/TokenItemRepository.h"

#include "RepositoryManager.h"

#include <QDebug>

RepositoryManager::RepositoryManager() {
    insertRepository(new MapRepository);
    insertRepository(new SpriteRepository);
    insertRepository(new TokenItemRepository);

    qDebug() << m_Repositories.count();
}

RepositoryManager::~RepositoryManager() {
    qDebug() << "was here";
}

Repository *RepositoryManager::getRepositoryByTableName(QString tableName) {
    if (m_Repositories.contains(tableName)) {
        qDebug() << "m_Repositories contains " + tableName;
        return m_Repositories.value(tableName);
    }
    else {
        qDebug() << "m_Repositories does not contain " + tableName;
    }
}

void RepositoryManager::insertRepository(Repository *repository) {
    m_Repositories.insert(repository->getTableName(), repository);
}
