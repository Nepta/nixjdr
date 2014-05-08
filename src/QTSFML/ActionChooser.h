#ifndef __ActionChooser_H__
#define __ActionChooser_H__

#include <vector>
#include "Canvas.h"
#include "Action.h"
#include "SpriteList.h"
/**
 * @brief The ActionChooser class
 * Action factory, create and initialize action according to its attribute
 */
class ActionChooser{
	/**
	 * @brief selectedSprite_
	 * point to a selected sprite when user press mouse or is null
	 */
	sf::Sprite *selectedSprite_ = nullptr;
	/**
	 * @brief isMovementAnimation_
	 * true if user is draging a sprite
	 */
	bool isMovementAnimation_ = false;

private:
	ActionChooser(){}
	enum ActionType{
		Cout,
		Remove,
		Add,
		Move
	};
	
public:
	/**
	 * @brief instance
	 * @return the unique instance of ActionChooser factory
	 */
	static ActionChooser& instance();
	/**
	 * @brief choose
	 * @param x x mouse position when click is released
	 * @param y y mouse position when click is released
	 * @return an action to perform
	 */
	Action& choose(int x, int y, SpriteList &spriteList);
	/**
	 * @brief selectSprite
	 * @param x x mouse position when click is released
	 * @param y y mouse position when click is released
	 * last clicked sprite
	 */
	void selectSprite(sf::Sprite *selectedSprite);
	/**
	 * @brief selectAction
	 * @param x mouse position when click is released
	 * @param y mouse position when click is released
	 * @return an action to perform
	 * hold logic to select action to perform
	 */
	ActionType selectAction(sf::Sprite *sprite);
	/**
	 * @brief isMoving
	 * @param state true if user is dragin a sprite
	 */
	void isMoving(bool state);
};

#endif /* __ActionChooser_H__ */

