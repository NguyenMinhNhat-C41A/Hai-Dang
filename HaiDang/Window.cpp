#include "Window.h"

Window::Window()
{
	this->windowLength = 1600;
	this->windowWidth = 960;
	this->window = new sf::RenderWindow(sf::VideoMode(this->windowLength, this->windowWidth), "Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);

}

int Window::getWindowLength() {
	return this->windowLength;
}

int Window::getWindowWidth() {
	return this->windowWidth;
}

sf::RenderWindow* Window::getWindow()
{
	return this->window;
}
