#include "Player.h"
#include <iostream>

void Player::initPlayerTexture(std::string textureLink)
{
	if (!this->playerTexture.loadFromFile(textureLink)) {
		std::cout << "Failed load: Player Texture" << std::endl;
		system("pause");
	};
}

void Player::initPlayerSprite(float pX, float pY)
{
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setPosition(pX, pY);
	sf::Rect<float> size = this->playerSprite.getGlobalBounds();

	this->playerSprite.setOrigin(sf::Vector2f(size.width / 2, size.height/2));

	this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
	this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);
}


Player::Player(float pX, float pY)
{
	this->initPlayerTexture("../img/Pl-T.png");
	this->initPlayerSprite(pX, pY);
	this->stepSize = 32.f;
	this->animationDelay = sf::seconds(0.0f);
}

sf::Vector2f Player::getPlayerGridPosition()
{
	return sf::Vector2f(this->gridPosX, this->gridPosY);
}

void Player::step(World world)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->stepLeft(world);
		std::cout << "x: " << this->gridPosX << ", y: " << this->gridPosY << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->stepRight(world);
		std::cout << "x: " << this->gridPosX << ", y: " << this->gridPosY << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->stepUp(world);
		std::cout << "x: " << this->gridPosX << ", y: " << this->gridPosY << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->stepDown(world);
		std::cout << "x: " << this->gridPosX << ", y: " << this->gridPosY << std::endl;
		
	}


}

void Player::stepUp(World world)
{
	int newGridPosY = this->gridPosY - 1;
	WorldTile tile = world.getTile(this->gridPosX, newGridPosY);
	if (tile.isTilePassable()) {
		for (int i = 0; i < this->stepSize; i++) {
			clock.restart();
			while (clock.getElapsedTime() < this->animationDelay)
			{
			}
			this->playerSprite.move(0.f, -1.f);
		}
		this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);
	}
}

void Player::stepDown(World world)
{
	int newGridPosY = this->gridPosY + 1;
	WorldTile tile = world.getTile(this->gridPosX, newGridPosY);
	if (tile.isTilePassable()) {
		for (int i = 0; i < this->stepSize; i++) {
			clock.restart();
			while (clock.getElapsedTime() < this->animationDelay)
			{
			}
			this->playerSprite.move(0.f, 1.f);
		}
		this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);

	}
}

void Player::stepLeft(World world)
{
	int newGridPosX = this->gridPosX - 1;
	WorldTile tile = world.getTile(newGridPosX, this->gridPosY);
	if (tile.isTilePassable()) {
		for (int i = 0; i < this->stepSize; i++) {
			clock.restart();
			while (clock.getElapsedTime() < this->animationDelay)
			{
			}
			this->playerSprite.move(-1.f, 0.f);
		}
		this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
	}
}

void Player::stepRight(World world)
{
	int newGridPosX = this->gridPosX + 1;
	WorldTile tile = world.getTile(newGridPosX, this->gridPosY);
	if (tile.isTilePassable()) {
		for (int i = 0; i < this->stepSize; i++) {
			clock.restart();
			while (clock.getElapsedTime() < this->animationDelay)
			{
			}
			this->playerSprite.move(1.f, 0.f);
		}
		this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
	}
}

void Player::renderPlayer(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}


void Player::playerUpdate(World world)
{
	this->step(world);

}


