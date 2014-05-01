#include <SFML/Graphics.hpp>

class Map{
	sf::RenderWindow* window_;
	sf::Texture backgroundImage_;
	sf::Sprite *background_;
	
public:
	Map(std::string);
	void unlimitRender();
};

