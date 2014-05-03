#ifndef __SpriteList_H__
#define __SpriteList_H__

#include <SFML/Graphics.hpp>

class SpriteList{
public: std::vector<std::pair<sf::Texture, std::vector<sf::Sprite>>> list_; //R.A.C.H.E.
private:
	SpriteList(){};
	SpriteList(const SpriteList&) = delete;
	SpriteList& operator=(const SpriteList&) = delete;
	
public:
	static SpriteList& instance();
	void newTexture(sf::Texture);
	void addSprite(int x, int y, int position=0);
};

#endif /* __SpriteList_H__ */

