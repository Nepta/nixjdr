#ifndef __ActionChooser_H__
#define __ActionChooser_H__

#include <vector>
#include "QTSFMLCanvas.h"
#include "Action.h"

typedef std::vector<std::pair<sf::Texture, std::vector<sf::Sprite>>> SpriteList;
class ActionChooser{
	SpriteList *spriteList_;
private:
	ActionChooser(){};

public:
	static ActionChooser& instance();
	void spriteList(SpriteList& spriteList);
	SpriteList& spriteList();
	Action* choose(int x, int y);
};

#endif /* __ActionChooser_H__ */

