#include <SFML/Graphics.hpp>

using namespace sf;

int main(){
	RenderWindow window(VideoMode(800,600),"map");
	Vector2u window_size = window.getSize();

	RectangleShape background(
        Vector2f(window_size.x, window_size.y));
    background.setPosition(0, 0);
    background.setFillColor(Color(3, 2, 18));

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if (event.type == Event::Closed){
				window.close();
			}
		}
		window.clear();
		window.draw(background);
		window.display();
	}
 return 0;
}
