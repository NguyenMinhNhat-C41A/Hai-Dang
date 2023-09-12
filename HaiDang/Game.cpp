#include"Game.h"

Game::Game() {
	this->window = new Window();
	this->player = new Player((float)((this->window->getWindowLength() / 2) - 16), (float)((this->window->getWindowWidth() / 2) - 16));
	//this->enemies.push_back(new Enemy((float)((this->window->getWindowLength() / 2) + 16), (float)((this->window->getWindowWidth() / 2) + 16), 32, 32, "../img/QuaiVat/Q-1.png"));
	this->enemy = new Enemy((float)((this->window->getWindowLength() / 2) + 16), (float)((this->window->getWindowWidth() / 2) + 16), 32, 32, "../img/QuaiVat/Q-1.png");
	this->world = new World();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->enemy;
	delete this->world;
}

void Game::run()
{
	sf::Clock clock;
	float dtFRIM;

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
		dtFRIM = clock.restart().asSeconds();
		this->player->playerUpdate(*world, dt, roundf(dtFRIM * 100) / 100);
		this->enemy->EnemyUpdate(*world, *player, dt, roundf(dtFRIM * 100) / 100);
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
	this->enemy->renderEnemy(*this->window->getWindow());
	this->window->getWindow()->display();

}
