#pragma once
#include <SFML/Graphics.hpp>
class Window {
private: 
	int windowLength;
	int windowWidth;
	sf::RenderWindow* window;
public:
	Window();

	int getWindowLength();
	
	int getWindowWidth();

	sf::RenderWindow* getWindow();
};