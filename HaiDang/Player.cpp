#include "Player.h"
#include <iostream>

void Player::initPlayerTexture(std::string textureLink)
{
	if (!this->playerTexture.loadFromFile(textureLink)) {
		std::cout << "Failed load: Player Texture" << std::endl;
		system("pause");
	};
}

void Player::setPlayerTextureRect(int x, int y, int l, int w)
{
	this->playerTextureRect = sf::IntRect(x,y,l,w);
	this->playerSprite.setTextureRect(this->playerTextureRect);
 }

void Player::initPlayerSprite(float pX, float pY)
{
	this->playerSprite.setTexture(this->playerTexture);
	this->setPlayerTextureRect(0, 0, 32, 32);
	this->playerSprite.setPosition(pX, pY);
	sf::Rect<float> size = this->playerSprite.getGlobalBounds();

	this->playerSprite.setOrigin(sf::Vector2f(size.width / 2, size.height / 2));

	this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
	this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);
}


Player::Player(float pX, float pY)
{
	this->initPlayerTexture("../img/NguoiChoi/NgCh.png");
	this->initPlayerSprite(pX, pY);
	this->stepSize = 4.f;

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
	int newGridPosY = (this->playerSprite.getPosition().y - 16 - this->stepSize)/32;
	if (world.getTile(this->gridPosX, newGridPosY).isTilePassable()) {
		this->playerSprite.move(0.f, -this->stepSize);
		this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);
	}

}

void Player::stepDown(World world)
{
	int newGridPosY = (this->playerSprite.getPosition().y + 15 + this->stepSize) / 32;
	if (world.getTile(this->gridPosX, newGridPosY).isTilePassable()) {

		this->playerSprite.move(0.f, this->stepSize);
		this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);

	}
}

void Player::stepLeft(World world)
{
	int newGridPosX = (this->playerSprite.getPosition().x - 16 - this->stepSize) / 32;
	if (world.getTile(newGridPosX, this->gridPosY).isTilePassable()) {

		this->playerSprite.move(-this->stepSize, 0.f);
		this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
	}
}

void Player::stepRight(World world)
{
	int newGridPosX = (this->playerSprite.getPosition().x + 15 + this->stepSize) / 32;
	if (world.getTile(newGridPosX, this->gridPosY).isTilePassable()) {
			
		this->playerSprite.move(this->stepSize, 0.f);
		this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
	}
}

void Player::adjustPos(World world)
{
	float tileX = world.getTile(this->gridPosX, this->gridPosY).getTileSprite().getPosition().x + 16;
	if (tileX != this->playerSprite.getPosition().x) {
		this->playerSprite.setPosition(tileX, this->playerSprite.getPosition().y);
	};

	float tileY = world.getTile(this->gridPosX, this->gridPosY).getTileSprite().getPosition().y + 16;
	if (tileY != this->playerSprite.getPosition().y) {
		this->playerSprite.setPosition(this->playerSprite.getPosition().x, tileY);
	};
}

void Player::animIdle()
{
	if (this->clock.getElapsedTime().asSeconds() > 2.f) {
		this->setPlayerTextureRect((this->playerTextureRect.left + 32)%128, this->playerTextureRect.top, 32, 32);
	}
}

void Player::animRun()
{

}

void Player::renderPlayer(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}


void Player::playerUpdate(World world)
{
	this->animIdle();
	this->step(world);
}

Animation::Animation(int x, int y, int w, int h, std::string textureLink)
{


}
