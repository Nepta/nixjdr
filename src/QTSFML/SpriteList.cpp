#include "SpriteList.h"

void SpriteList::addSprite(int x, int y){
    sf::Texture *texture = new sf::Texture(tokenTextureToLoad_);
    sf::Sprite sprite(*texture);
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
