#include "SpriteList.h"
#include <iostream>
#include <vector>

void SpriteList::newTexture(sf::Texture& texture){
	std::vector<sf::Sprite> sprite;
	list_.push_back({texture, sprite});
}

void SpriteList::addSprite(int x, int y, int position){
	sf::Sprite sprite(list_[position].first);
	sprite.setPosition(x,y);
	list_[position].second.push_back(sprite);
}

void SpriteList::delSprite(int x, int y, int position){
	sf::Vector2f cellPosition(x,y);
	for(auto &texturedSprite : list_){
		for(auto it = texturedSprite.second.begin(); it < texturedSprite.second.end(); it++){
			sf::Sprite& sprite = *it;
			if(sprite.getPosition() == cellPosition){
				list_[position].second.erase(it);
			}
		}
	}
}

sf::Sprite* SpriteList::searchSprite(int x, int y){
	sf::Vector2f cellPosition(x,y);
	for(auto &texturedSprite : list_){
		for(auto &sprite : texturedSprite.second){
			if(sprite.getPosition() == cellPosition){
				return &sprite;
			}
		}
	}
	return nullptr;
}
