#include"Game.h"

Game::Game() {
	this->window = new Window();
	this->player = new Player((float)((this->window->getWindowLength() / 2) - 16), (float)((this->window->getWindowWidth() / 2) - 16));
	this->world = new World();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->world;
}

void Game::run()
{
	while (this->window->getWindow()->isOpen()) {
		this->update();
		this->render();
	}
}

void Game::update()
{
	sf::Event windowEvent;
	while (this->window->getWindow()->pollEvent(windowEvent)) {

		switch (windowEvent.type)
		{
		case sf::Event::Closed:
			this->window->getWindow()->close();
			break;

		case sf::Event::KeyPressed:
			if (windowEvent.key.code == sf::Keyboard::Escape) {
				this->window->getWindow()->close();
			}
			break;

		}
	}
	this->player->playerUpdate(*world);

}

void Game::render()
{
	this->window->getWindow()->clear();
	this->world->renderWorld(*this->window->getWindow());
	this->player->renderPlayer(*this->window->getWindow());
	this->window->getWindow()->display();

}
