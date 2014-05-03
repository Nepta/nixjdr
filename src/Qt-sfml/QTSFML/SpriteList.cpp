#include "SpriteList.h"
#include <vector>

SpriteList& SpriteList::instance(){
	static SpriteList *instance = new SpriteList();
	return *instance;
}

void SpriteList::newTexture(sf::Texture texture){
	std::vector<sf::Sprite> sprite;
	list_.push_back({texture, sprite});
}

void SpriteList::addSprite(int x, int y, int position){
	sf::Sprite sprite(list_[position].first);
	sprite.setPosition(x,y);
	list_[position].second.push_back(sprite);
}

sf::Sprite* SpriteList::searchSprite(int x, int y){
	sf::Vector2f cellPosition(x,y);
	for(auto &texturedSprite : list_){
		for(auto &sprite : texturedSprite.second){
			if(sprite.getPosition == cellPosition){
				return &sprite;
			}
		}
	}
}
