#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include "Database/Repository/MapRepository.h"
#include "Database/Repository/SpriteRepository.h"
#include "Database/Repository/TokenItemRepository.h"

class RepositoryManager
{
public:
    static MapRepository s_MapRepository;
    static SpriteRepository s_SpriteRepository;
    static TokenItemRepository s_TokenItemRepository;
};

#endif // REPOSITORYMANAGER_H
