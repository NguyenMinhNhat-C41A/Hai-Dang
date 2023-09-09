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
	this->stepSize = 1.f;
	this->stepMultiplayer = 256;

	anims[int(AnimIndex::Idle)] = PlayerAnimation(0, 0, 32, 32, "../img/NguoiChoi/NgCh.png");
	anims[int(AnimIndex::Up)] = PlayerAnimation(0, 32, 32, 32, "../img/NguoiChoi/NgCh.png");
	anims[int(AnimIndex::Left)] = PlayerAnimation(0, 64, 32, 32, "../img/NguoiChoi/NgCh.png");
	anims[int(AnimIndex::Down)] = PlayerAnimation(0, 96, 32, 32, "../img/NguoiChoi/NgCh.png");
	anims[int(AnimIndex::Right)] = PlayerAnimation(0, 128, 32, 32, "../img/NguoiChoi/NgCh.png");
	this->currentAnim = AnimIndex::Idle;
	
}

sf::Vector2f Player::getPlayerGridPosition()
{
	return sf::Vector2f(this->gridPosX, this->gridPosY);
}

void Player::step(World world, float dtFRIM)
{	
	this->currentAnim = AnimIndex::Idle;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "Left" << std::endl;
		this->currentAnim = AnimIndex::Left;
		this->stepLeft(world, dtFRIM);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		std::cout << "Right" << std::endl;
		this->currentAnim = AnimIndex::Right;
		this->stepRight(world, dtFRIM);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		std::cout << "Up" << std::endl;
		this->currentAnim = AnimIndex::Up;
		this->stepUp(world, dtFRIM);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
	{
		std::cout << "Down" << std::endl;
		this->currentAnim = AnimIndex::Down;
		this->stepDown(world, dtFRIM);
	}
}

void Player::stepUp(World world, float dtFRIM)
{	
	int temp = (int)(this->stepSize * dtFRIM * this->stepMultiplayer);
	int newGridPosY = (this->playerSprite.getPosition().y - (this->playerTextureRect.width / 2) - temp)/32;
	int newGridPosLeftX = (this->playerSprite.getPosition().x - (this->playerTextureRect.width / 2)) / 32;
	int newGridPosRightX = (this->playerSprite.getPosition().x + ((this->playerTextureRect.width / 2) - 1)) / 32;
	bool check1 = world.getTile(newGridPosLeftX, newGridPosY).isTilePassable();
	bool check2 = world.getTile(newGridPosRightX, newGridPosY).isTilePassable();

	/*std::cout << "Check1 - Pass: " << check1 << " - Pos: x = " << world.getTile(newGridPosLeftX, newGridPosY).getTileSprite().getPosition().x << ",y =  " << world.getTile(newGridPosLeftX, newGridPosY).getTileSprite().getPosition().y << std::endl;
	std::cout << "Check2 - Pass: " << check2 << " - Pos: x = " << world.getTile(newGridPosRightX, newGridPosY).getTileSprite().getPosition().x << ",y =  " << world.getTile(newGridPosRightX, newGridPosY).getTileSprite().getPosition().y << std::endl;*/

	if (world.getTile(newGridPosLeftX, newGridPosY).isTilePassable() && world.getTile(newGridPosRightX, newGridPosY).isTilePassable()) {
		this->playerSprite.move(0.f, -temp);
	}
	else {
		WorldTile currentTile = world.getTile(this->gridPosX, this->gridPosY);
		this->playerSprite.move( 0.f, - (int)(abs((int)this->playerSprite.getPosition().y - currentTile.getTileSprite().getPosition().y)));
	}
	this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);
}

void Player::stepDown(World world, float dtFRIM)
{
	int temp = (int)(this->stepSize * dtFRIM * this->stepMultiplayer);
	int newGridPosY = (this->playerSprite.getPosition().y + ((this->playerTextureRect.width / 2) - 1) + temp) / 32;
	int newGridPosLeftX = (this->playerSprite.getPosition().x - (this->playerTextureRect.width / 2)) / 32;
	int newGridPosRightX = (this->playerSprite.getPosition().x + ((this->playerTextureRect.width / 2) - 1)) / 32;
	bool check1 = world.getTile(newGridPosLeftX, newGridPosY).isTilePassable();
	bool check2 = world.getTile(newGridPosRightX, newGridPosY).isTilePassable();

	/*std::cout << "Check1 - Pass: " << check1 << " - Pos: x = " << world.getTile(newGridPosLeftX, newGridPosY).getTileSprite().getPosition().x << ",y =  " << world.getTile(newGridPosLeftX, newGridPosY).getTileSprite().getPosition().y << std::endl;
	std::cout << "Check2 - Pass: " << check2 << " - Pos: x = " << world.getTile(newGridPosRightX, newGridPosY).getTileSprite().getPosition().x << ",y =  " << world.getTile(newGridPosRightX, newGridPosY).getTileSprite().getPosition().y << std::endl;*/

	if (world.getTile(newGridPosLeftX, newGridPosY).isTilePassable() && world.getTile(newGridPosRightX, newGridPosY).isTilePassable()) {
		this->playerSprite.move(0.f, temp);
		this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);
	}

	else {
		WorldTile currentTile = world.getTile(this->gridPosX, this->gridPosY);
		this->playerSprite.move(0.f, (int)(abs(currentTile.getTileSprite().getPosition().y) - (int)this->playerSprite.getPosition().y));

	}
	this->gridPosY = (int)((this->playerSprite.getPosition().y) / 32);
}

void Player::stepLeft(World world, float dtFRIM)
{
	int temp = (int)(this->stepSize * dtFRIM * this->stepMultiplayer);
	int newGridPosX = (this->playerSprite.getPosition().x - (this->playerTextureRect.width / 2) - temp) / 32;
	int newGridPosUpY = (this->playerSprite.getPosition().y - (this->playerTextureRect.width / 2)) / 32;
	int newGridPosDownY = (this->playerSprite.getPosition().y + ((this->playerTextureRect.width / 2) - 1)) / 32;

	bool check1 = world.getTile(newGridPosX, newGridPosUpY).isTilePassable();
	bool check2 = world.getTile(newGridPosX, newGridPosDownY).isTilePassable();

	/*std::cout << "Check1 - Pass: " << check1 << " - Pos: x = " << world.getTile(newGridPosX, newGridPosUpY).getTileSprite().getPosition().x << ",y =  " << world.getTile(newGridPosX, newGridPosUpY).getTileSprite().getPosition().y << std::endl;
	std::cout << "Check2 - Pass: " << check2 << " - Pos: x = " << world.getTile(newGridPosX, newGridPosDownY).getTileSprite().getPosition().x << ",y =  " << world.getTile(newGridPosX, newGridPosDownY).getTileSprite().getPosition().y << std::endl;*/

	if (world.getTile(newGridPosX, newGridPosUpY).isTilePassable() && world.getTile(newGridPosX, newGridPosDownY).isTilePassable()) {
		this->playerSprite.move(-temp, 0.f);
	}
	else {
		WorldTile currentTile = world.getTile(this->gridPosX, this->gridPosY);
		this->playerSprite.move(-(int)(abs((int)this->playerSprite.getPosition().x - currentTile.getTileSprite().getPosition().x)), 0.f);
	}

	this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
}

void Player::stepRight(World world, float dtFRIM)
{
	int temp = (int)(this->stepSize * dtFRIM * this->stepMultiplayer);
	int newGridPosX = (this->playerSprite.getPosition().x + ((this->playerTextureRect.width / 2) - 1) + temp) / 32;
	int newGridPosUpY = (this->playerSprite.getPosition().y - (this->playerTextureRect.width / 2)) / 32;
	int newGridPosDownY = (this->playerSprite.getPosition().y + ((this->playerTextureRect.width / 2) - 1)) / 32;
	
	bool check1 = world.getTile(newGridPosX, newGridPosUpY).isTilePassable();
	bool check2 = world.getTile(newGridPosX, newGridPosDownY).isTilePassable();

	/*std::cout << "Check1 - Pass: " << check1 << " - Pos: x = " << world.getTile(newGridPosX, newGridPosUpY).getTileSprite().getPosition().x << ",y =  " << world.getTile(newGridPosX, newGridPosUpY).getTileSprite().getPosition().y << std::endl;
	std::cout << "Check2 - Pass: " << check2 << " - Pos: x = " << world.getTile(newGridPosX, newGridPosDownY).getTileSprite().getPosition().x << ",y =  " << world.getTile(newGridPosX, newGridPosDownY).getTileSprite().getPosition().y << std::endl;*/

	if (world.getTile(newGridPosX, newGridPosUpY).isTilePassable() && world.getTile(newGridPosX, newGridPosDownY).isTilePassable()) {
		this->playerSprite.move(temp, 0.f);
	}

	else {
		WorldTile currentTile = world.getTile(this->gridPosX, this->gridPosY);
		this->playerSprite.move((int)(abs(currentTile.getTileSprite().getPosition().x - (int)this->playerSprite.getPosition().x)), 0.f);
	}

	this->gridPosX = (int)((this->playerSprite.getPosition().x) / 32);
}

void Player::renderPlayer(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}


void Player::playerUpdate(World world, float dt, float dtFRIM)
{
	this->step(world, dtFRIM);
	anims[int(this->currentAnim)].update(dt);
	anims[int(this->currentAnim)].setToSprite(this->playerSprite);
}

PlayerAnimation::PlayerAnimation(int x, int y, int w, int h, std::string textureLink)
{
	if (!this->texture.loadFromFile(textureLink)) {
		std::cout << "Failed load: Animation Texture" << std::endl;
		system("pause");
	};
	for (int i = 0; i < this->numFrames; i++) {
		frames[i] = {x + i * w, y, w, h};
	}

}

void PlayerAnimation::setToSprite(sf::Sprite& s) const
{	
	s.setTexture(this->texture);
	s.setTextureRect(this->frames[this->frameIndex]);	
}

void PlayerAnimation::update(float dt)
{
	this->time += dt;
	//std::cout << "time: " << this->time << std::endl;
	while (time >= animDelay) {
		time -= animDelay;
		//std::cout << "time-AS: " << this->time << std::endl;
		this->advance();
	}
}

void PlayerAnimation::advance()
{

	if (++frameIndex >= numFrames) {
		frameIndex = 0;
	}
}
