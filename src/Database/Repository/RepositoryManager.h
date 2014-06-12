#ifndef REPOSITORYMANAGER_H
#define REPOSITORYMANAGER_H

#include "Database/Repository/SpriteRepository.h"
#include "Database/Repository/TokenItemRepository.h"
#include "Database/Repository/MapRepository.h"
#include "Database/Repository/BackgroundLayerRepository.h"
#include "Database/Repository/MapLayerRepository.h"
#include "Database/Repository/FoWLayerRepository.h"
#include "Database/Repository/DrawingLayerRepository.h"
#include "Database/Repository/GameObjectRepository.h"
#include "Database/Repository/CharacterRepository.h"

class RepositoryManager
{
public:
    static SpriteRepository s_SpriteRepository;
    static TokenItemRepository s_TokenItemRepository;
    static MapRepository s_MapRepository;
    static BackgroundLayerRepository s_BgLayerRepository;
    static MapLayerRepository s_MapLayerRepository;
    static FoWLayerRepository s_FoWLayerRepository;
    static DrawingLayerRepository s_DrawingLayerRepository;
    static GameObjectRepository s_GameObjectRepository;
    static CharacterRepository s_CharacterRepository;
};

#endif // REPOSITORYMANAGER_H
