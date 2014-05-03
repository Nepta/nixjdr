#ifndef __SpriteList_H__
#define __SpriteList_H__

#include <SFML/Graphics.hpp>

class SpriteList{
	std::vector<std::pair<sf::Texture, std::vector<sf::Sprite>>> list_;
private:
	SpriteList(){};
	SpriteList(const SpriteList&) = delete;
	SpriteList& operator=(const SpriteList&) = delete;
public:
	static 
};

#endif /* __SpriteList_H__ */

