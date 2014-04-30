#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main(){
	RenderWindow window(VideoMode(800,600),"map");
	window.setFramerateLimit(120);
	Texture forest;
	if(!forest.loadFromFile("resource/littleForest.png")){
		std::cout << "unable to load littleForest.png" << std::endl;
	}
	
	Sprite background(forest);
	
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape)){
				window.close();
			}
		}
		window.clear();
		window.draw(background);
		window.display();
	}
 return 0;
}
