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

	anims[int(AnimIndex::Idle)] = Animation(0, 0, 32, 32, "../img/NguoiChoi/NgCh.png");
	anims[int(AnimIndex::Up)] = Animation(0, 32, 32, 32, "../img/NguoiChoi/NgCh.png");
	anims[int(AnimIndex::Left)] = Animation(0, 64, 32, 32, "../img/NguoiChoi/NgCh.png");
	anims[int(AnimIndex::Down)] = Animation(0, 96, 32, 32, "../img/NguoiChoi/NgCh.png");
	anims[int(AnimIndex::Right)] = Animation(0, 128, 32, 32, "../img/NguoiChoi/NgCh.png");
	this->currentAnim = AnimIndex::Idle;
	
}

sf::Vector2f Player::getPlayerGridPosition()
{
	return sf::Vector2f(this->gridPosX, this->gridPosY);
}

void Player::step(World world)
{	
	this->currentAnim = AnimIndex::Idle;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->currentAnim = AnimIndex::Left;
		this->stepLeft(world);
		//std::cout << "x: " << this->gridPosX << ", y: " << this->gridPosY << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->currentAnim = AnimIndex::Right;
		this->stepRight(world);
		//std::cout << "x: " << this->gridPosX << ", y: " << this->gridPosY << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->currentAnim = AnimIndex::Up;
		this->stepUp(world);
		//std::cout << "x: " << this->gridPosX << ", y: " << this->gridPosY << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->currentAnim = AnimIndex::Down;
		this->stepDown(world);
		//std::cout << "x: " << this->gridPosX << ", y: " << this->gridPosY << std::endl;

	}
}

void Player::stepUp(World world)
{	
	int newGridPosY = (this->playerSprite.getPosition().y - 16 - this->stepSize)/32;
	int newGridPosLeftX = (this->playerSprite.getPosition().x - 16) / 32;
	int newGridPosRightX = (this->playerSprite.getPosition().x + 15) / 32;
	if (world.getTile(newGridPosLeftX, newGridPosY).isTilePassable() && world.getTile(newGridPosRightX, newGridPosY).isTilePassable()) {
		this->playerSprite.move(0.f, -this->stepSize);
		this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);
	}

}

void Player::stepDown(World world)
{
	int newGridPosY = (this->playerSprite.getPosition().y + 15 + this->stepSize) / 32;
	int newGridPosLeftX = (this->playerSprite.getPosition().x - 16) / 32;
	int newGridPosRightX = (this->playerSprite.getPosition().x + 15) / 32;
	if (world.getTile(newGridPosLeftX, newGridPosY).isTilePassable() && world.getTile(newGridPosRightX, newGridPosY).isTilePassable()) {
		this->playerSprite.move(0.f, this->stepSize);
		this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);

	}
}

void Player::stepLeft(World world)
{
	int newGridPosX = (this->playerSprite.getPosition().x - 16 - this->stepSize) / 32;
	int newGridPosUpY = (this->playerSprite.getPosition().y -16) / 32;
	int newGridPosDownY = (this->playerSprite.getPosition().y + 15) / 32;
	if (world.getTile(newGridPosX, newGridPosUpY).isTilePassable() && world.getTile(newGridPosX, newGridPosDownY).isTilePassable()) {

		this->playerSprite.move(-this->stepSize, 0.f);
		this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
	}

	else {
	}
}

void Player::stepRight(World world)
{
	int newGridPosX = (this->playerSprite.getPosition().x + 15 + this->stepSize) / 32;
	int newGridPosUpY = (this->playerSprite.getPosition().y - 16) / 32;
	int newGridPosDownY = (this->playerSprite.getPosition().y + 15) / 32;
	if (world.getTile(newGridPosX, newGridPosUpY).isTilePassable() && world.getTile(newGridPosX, newGridPosDownY).isTilePassable()) {
			
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


void Player::renderPlayer(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}


void Player::playerUpdate(World world, float dt)
{
	this->step(world);
	anims[int(this->currentAnim)].update(dt);
	anims[int(this->currentAnim)].setToSprite(this->playerSprite);
}

Animation::Animation(int x, int y, int w, int h, std::string textureLink)
{
	if (!this->texture.loadFromFile(textureLink)) {
		std::cout << "Failed load: Animation Texture" << std::endl;
		system("pause");
	};
	for (int i = 0; i < this->numFrames; i++) {
		frames[i] = {x + i * w, y, w, h};
	}

}

void Animation::setToSprite(sf::Sprite& s) const
{	
	s.setTexture(this->texture);
	s.setTextureRect(this->frames[this->frameIndex]);	
}

void Animation::update(float dt)
{
	
	this->time += dt;
	//std::cout << "time: " << this->time << std::endl;
	while (time >= animDelay) {
		time -= animDelay;
		//std::cout << "time-AS: " << this->time << std::endl;
		this->advance();
	}
}

void Animation::advance()
{

	if (++frameIndex >= numFrames) {
		frameIndex = 0;
	}
}
