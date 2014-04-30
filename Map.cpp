#include <SFML/Window.hpp>

using namespace sf;

int main(){
	Window window(VideoMode(800,600),"map");
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
			}
		}
	}
 return 0;
}
