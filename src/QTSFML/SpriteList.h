#ifndef __SpriteList_H__
#define __SpriteList_H__

#include <SFML/Graphics.hpp>

class SpriteList{
public:
    /**
     * @brief list_ - List of texture paired with its sprite list.
     */
    std::vector<std::pair<sf::Texture&,sf::Sprite>> list_;
    sf::Texture tokenTextureToLoad_;

public:
    /**
     * Look for the sprite placed at (x,y)
     *
     * @brief searchSprite
     * @param x
     * @param y
     * @return The sprite at (x,y)
     */
	sf::Sprite* searchSprite(int x, int y);

    /**
     * Add a new sprite to the list of a texture
     *
     * @brief addSprite
     * @param x
     * @param y
     * @param position
     */
    void addSprite(int x, int y); //add a sprite in the list at the position (texture number)

    /**
     * Remove a sprite of the list of a texture
     *
     * @brief delSprite
     * @param x
     * @param y
     * @param position
     */
    void delSprite(int x, int y); //add a sprite in the list at the position (texture number)
};

#endif /* __SpriteList_H__ */

