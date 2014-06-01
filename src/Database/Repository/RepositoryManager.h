#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include "Database/Repository/SpriteRepository.h"
#include "Database/Repository/TokenItemRepository.h"
#include "Database/Repository/MapRepository.h"
#include "Database/Repository/MapLayerRepository.h"

class RepositoryManager
{
public:
    static SpriteRepository s_SpriteRepository;
    static TokenItemRepository s_TokenItemRepository;
    static MapRepository s_MapRepository;
    static MapLayerRepository s_MapLayerRepository;
};

#endif // REPOSITORYMANAGER_H
