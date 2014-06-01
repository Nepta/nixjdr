#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include "Database/Repository/SpriteRepository.h"
#include "Database/Repository/TokenItemRepository.h"
#include "Database/Repository/MapRepository.h"
#include "Database/Repository/MapLayerRepository.h"
#include "Database/Repository/FoWLayerRepository.h"

class RepositoryManager
{
public:
    static SpriteRepository s_SpriteRepository;
    static TokenItemRepository s_TokenItemRepository;
    static MapRepository s_MapRepository;
    static MapLayerRepository s_MapLayerRepository;
    static FoWLayerRepository s_FoWLayerRepository;
};

#endif // REPOSITORYMANAGER_H
