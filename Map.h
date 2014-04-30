#include <SFML/Graphics.hpp>

class Map{
	sf::RenderWindow* window_;

public:
	Map(std::string);
	void unlimitRender();
};

