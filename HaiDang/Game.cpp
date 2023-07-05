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
	auto tp = std::chrono::steady_clock::now();
	while (this->window->getWindow()->isOpen()) {
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
		float dt;
		{
			const auto new_tp = std::chrono::steady_clock::now();
			dt = std::chrono::duration<float>(new_tp - tp).count();
			tp = new_tp;
		}
		this->player->playerUpdate(*world, dt);
		this->render();
	}

}

void Game::update()
{
	

}

void Game::render()
{
	this->window->getWindow()->clear();
	this->world->renderWorld(*this->window->getWindow());
	this->player->renderPlayer(*this->window->getWindow());
	this->window->getWindow()->display();

}
