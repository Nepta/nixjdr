#include "SpriteList.h"
#include <iostream>
#include <vector>

void SpriteList::addSprite(int x, int y){
    sf::Sprite sprite(tokenTextureToLoad_);
    sprite.setPosition(x,y);
    list_.push_back({tokenTextureToLoad_, sprite});
}

void SpriteList::delSprite(int x, int y){
    sf::Vector2f cellPosition(x,y);
    for(auto it = list_.begin(); it < list_.end(); it++){
        if((*it).second.getPosition() == cellPosition){
            list_.erase(it);
        }
    }
}

sf::Sprite* SpriteList::searchSprite(int x, int y){
    sf::Vector2f cellPosition(x,y);
    for(auto &item : list_){
        if(item.second.getPosition() == cellPosition){
            return &item.second;
        }
    }

    return nullptr;
}
