#ifndef __SpriteList_H__
#define __SpriteList_H__

#include <SFML/Graphics.hpp>

class SpriteList{
public: std::vector<std::pair<sf::Texture, std::vector<sf::Sprite>>> list_; //R.A.C.H.E.
private:
	SpriteList(){}; // private constructor, you can only access by instance() static methode
	SpriteList(const SpriteList&) = delete;
	SpriteList& operator=(const SpriteList&) = delete;
	
public:
	static SpriteList& instance();
	void newTexture(sf::Texture); //add a texture in the list
	void addSprite(int x, int y, int position=0); //add a sprite in the list at the position (texture number)
};

#endif /* __SpriteList_H__ */

