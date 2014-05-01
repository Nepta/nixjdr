#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "CoutAction.h"

using namespace sf;

Map::Map(std::string path){
	window_ = new RenderWindow(VideoMode(800,600),"map");
	
	if(!backgroundImage_.loadFromFile(path)){
		std::cout << "unable to load " << path << std::endl;
	}
	background_ = new Sprite(backgroundImage_);
}

void Map::unlimitRender(){
	while(window_->isOpen()){
		Event event;
		while(window_->pollEvent(event)){
			if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape)){
				window_->close();
			}
		}
		window_->clear();
		window_->draw(*background_);
		window_->display();
	}	
}

int main(){
	Map map("resource/suwako.png");
	CoutAction action(10,10);
	action.execute();
	map.unlimitRender();
 return 0;
}

