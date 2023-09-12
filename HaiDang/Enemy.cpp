#include "Enemy.h"

void Enemy::initEnemyTexture(std::string textureLink)
{
	if (!this->enemyTexture.loadFromFile(textureLink)) {
		std::cout << "Failed load: Enemy Texture" << std::endl;
		system("pause");
	};
}

void Enemy::setEnemyTextureRect(int x, int y, int l, int w)
{
	this->enemyTextureRect = sf::IntRect(x, y, l, w);
	this->enemySprite.setTextureRect(this->enemyTextureRect);
}

void Enemy::initEnemySprite(float pX, float pY, int l, int w)
{
	this->enemySprite.setTexture(this->enemyTexture);
	this->setEnemyTextureRect(0, 0, l, w);
	this->enemySprite.setPosition(pX, pY);
	sf::Rect<float> size = this->enemySprite.getGlobalBounds();
	this->enemySprite.setOrigin(sf::Vector2f(size.width / 2, size.height / 2));

	this->gridPosX = (int)((this->enemySprite.getPosition().x) / 32);
	this->gridPosY = (int)((this->enemySprite.getPosition().y) / 32);
}

Enemy::Enemy(float pX, float pY, int l, int w, std::string textureLink)
{
	this->initEnemyTexture(textureLink);
	this->initEnemySprite(pX, pY, l, w);

	this->stepSize = 1.f;
	this->stepMultiplayer = 256;
	this->stepDirection = 0;

	anims[int(AnimIndex::Idle)] = EnemyAnimation(0, 0, l, w, textureLink);
	anims[int(AnimIndex::Up)] = EnemyAnimation(0, w, l, w, textureLink);
	anims[int(AnimIndex::Left)] = EnemyAnimation(0, w * 2, l, w, textureLink);
	anims[int(AnimIndex::Down)] = EnemyAnimation(0, w * 3, l, w, textureLink);
	anims[int(AnimIndex::Right)] = EnemyAnimation(0, w * 4, l, w, textureLink);
	this->currentAnim = AnimIndex::Idle;
}

sf::Vector2f Enemy::getEnemyGridPosition()
{
	return sf::Vector2f(this->gridPosX, this->gridPosY);
}

void Enemy::step(World world, Player player, float dtFRIM)
{
	switch (this->stepDirection)
	{

	case 0:
		this->findPathToPlayer(player);
		this->stepNumsReset();
		break;
	
	case 1:
		
		if (this->stepNums > 0) {
			this->stepNums -= 1;
			this->currentAnim = AnimIndex::Up;
			this->stepUp(world, player, dtFRIM);
		}
		else {
			this->stepNumsReset();
			this->findPathToPlayer(player);
		}
		break;

	case 2:

		if (this->stepNums > 0) {
			this->stepNums -= 1;
			this->currentAnim = AnimIndex::Up;
			this->stepUp(world, player, dtFRIM);
			this->stepRight(world, player, dtFRIM);
			
		}
		else {
			this->stepNumsReset();
			this->findPathToPlayer(player);
		}
		break;

	case 3:
		
		if (this->stepNums > 0) {
			this->stepNums -= 1;
			this->currentAnim = AnimIndex::Right;
			this->stepRight(world, player, dtFRIM);
		}
		else {
			this->stepNumsReset();
			this->findPathToPlayer(player);
		}
		break;

	case 4:

		if (this->stepNums > 0) {
			this->stepNums -= 1;
			this->currentAnim = AnimIndex::Down;
			this->stepDown(world, player, dtFRIM);
			this->stepRight(world, player, dtFRIM);
		}
		else {
			this->stepNumsReset();
			this->findPathToPlayer(player);
		}
		break;

	case 5:

		if (this->stepNums > 0) {
			this->stepNums -= 1;
			this->currentAnim = AnimIndex::Down;
			this->stepDown(world, player, dtFRIM);
		}
		else {
			this->stepNumsReset();
			this->findPathToPlayer(player);
		}
		break;

	case 6:

		if (this->stepNums > 0) {
			this->stepNums -= 1;
			this->currentAnim = AnimIndex::Down;
			this->stepDown(world, player, dtFRIM);
			this->stepLeft(world, player, dtFRIM);
		}
		else {
			this->stepNumsReset();
			this->findPathToPlayer(player);
		}
		break;

	case 7:

		if (this->stepNums > 0) {
			this->stepNums -= 1;
			this->currentAnim = AnimIndex::Left;
			this->stepLeft(world, player, dtFRIM);
		}
		else {
			this->stepNumsReset();
			this->findPathToPlayer(player);
		}
		break;

	case 8:

		if (this->stepNums > 0) {
			this->stepNums -= 1;
			this->currentAnim = AnimIndex::Up;
			this->stepUp(world, player, dtFRIM);
			this->stepLeft(world, player, dtFRIM);
		}
		else {
			this->stepNumsReset();
			this->findPathToPlayer(player);
		}
		break;

	default:
		break;
	}
}

void Enemy::stepUp(World world, Player player, float dtFRIM)
{
	const int temp = (int)(this->stepSize * dtFRIM * this->stepMultiplayer);
	const int newGridPosY = (this->enemySprite.getPosition().y - (this->enemyTextureRect.width / 2) - temp) / 32;
	const int newGridPosLeftX = (this->enemySprite.getPosition().x - (this->enemyTextureRect.width / 2)) / 32;
	const int newGridPosRightX = (this->enemySprite.getPosition().x + ((this->enemyTextureRect.width / 2) - 1)) / 32;

	const bool passCheck1 = world.getTile(newGridPosLeftX, newGridPosY).isTilePassable();
	const bool passCheck2 = world.getTile(newGridPosRightX, newGridPosY).isTilePassable();

	if (passCheck1 && passCheck2) {
		this->enemySprite.move(0.f, -temp);
	}
	else {
		WorldTile currentTile = world.getTile(this->gridPosX, this->gridPosY);
		this->enemySprite.move(0.f, -(int)(abs((int)this->enemySprite.getPosition().y - currentTile.getTileSprite().getPosition().y)));

		this->stepNums = 0;
	}
	this->gridPosY = (int)((this->enemySprite.getPosition().y) / 32);
}

void Enemy::stepDown(World world, Player player, float dtFRIM)
{
	const int temp = (int)(this->stepSize * dtFRIM * this->stepMultiplayer);
	const int newGridPosY = (this->enemySprite.getPosition().y + ((this->enemyTextureRect.width / 2) - 1) + temp) / 32;
	const int newGridPosLeftX = (this->enemySprite.getPosition().x - (this->enemyTextureRect.width / 2)) / 32;
	const int newGridPosRightX = (this->enemySprite.getPosition().x + ((this->enemyTextureRect.width / 2) - 1)) / 32;

	const bool passCheck1 = world.getTile(newGridPosLeftX, newGridPosY).isTilePassable();
	const bool passCheck2 = world.getTile(newGridPosRightX, newGridPosY).isTilePassable();

	if (passCheck1 && passCheck2) {
		this->enemySprite.move(0.f, temp);
	}

	else {
		WorldTile currentTile = world.getTile(this->gridPosX, this->gridPosY);
		this->enemySprite.move(0.f, (int)(abs(currentTile.getTileSprite().getPosition().y) - (int)this->enemySprite.getPosition().y));

		this->stepNums = 0;

	}
	this->gridPosY = (int)((this->enemySprite.getPosition().y) / 32);
}

void Enemy::stepLeft(World world, Player player, float dtFRIM)
{
	const int temp = (int)(this->stepSize * dtFRIM * this->stepMultiplayer);
	const int newGridPosX = (this->enemySprite.getPosition().x - (this->enemyTextureRect.width / 2) - temp) / 32;
	const int newGridPosUpY = (this->enemySprite.getPosition().y - (this->enemyTextureRect.width / 2)) / 32;
	const int newGridPosDownY = (this->enemySprite.getPosition().y + ((this->enemyTextureRect.width / 2) - 1)) / 32;

	const bool passCheck1 = world.getTile(newGridPosX, newGridPosUpY).isTilePassable();
	const bool passCheck2 = world.getTile(newGridPosX, newGridPosDownY).isTilePassable();

	if (passCheck1 && passCheck2) {
		this->enemySprite.move(-temp, 0.f);
	}
	else {
		WorldTile currentTile = world.getTile(this->gridPosX, this->gridPosY);
		this->enemySprite.move(-(int)(abs((int)this->enemySprite.getPosition().x - currentTile.getTileSprite().getPosition().x)), 0.f);

		this->stepNums = 0;
	}

	this->gridPosX = (int)((this->enemySprite.getPosition().x) / 32);
}

void Enemy::stepRight(World world, Player player, float dtFRIM)
{
	const int temp = (int)(this->stepSize * dtFRIM * this->stepMultiplayer);
	const int newGridPosX = (this->enemySprite.getPosition().x + ((this->enemyTextureRect.width / 2) - 1) + temp) / 32;
	const int newGridPosUpY = (this->enemySprite.getPosition().y - (this->enemyTextureRect.width / 2)) / 32;
	const int newGridPosDownY = (this->enemySprite.getPosition().y + ((this->enemyTextureRect.width / 2) - 1)) / 32;

	const bool passCheck1 = world.getTile(newGridPosX, newGridPosUpY).isTilePassable();
	const bool passCheck2 = world.getTile(newGridPosX, newGridPosDownY).isTilePassable();

	if (passCheck1 && passCheck2) {
		this->enemySprite.move(temp, 0.f);
	}

	else {
		WorldTile currentTile = world.getTile(this->gridPosX, this->gridPosY);
		this->enemySprite.move((int)(abs(currentTile.getTileSprite().getPosition().x - (int)this->enemySprite.getPosition().x)), 0.f);

		this->stepNums = 0;
	}

	this->gridPosX = (int)((this->enemySprite.getPosition().x) / 32);
}

void Enemy::stepNumsReset()
{
	this->stepNums = rand() % 32 + 1;
}

void Enemy::findPathToPlayer(Player player)
{
	sf::Vector2f playerCoords = player.getPlayerPos();
	sf::Vector2f enemyCoords = this->enemySprite.getPosition();
	const double angle = -atan2(playerCoords.y - enemyCoords.y, playerCoords.x - enemyCoords.x) * (180 / (2 * acos(0.0)));
	std::cout << "angle: " << angle << std::endl;

	if (angle < 112.5 && angle > 67.5) {
		this->stepDirection = 1;
	}
	else if (angle <= 67.5 && angle >= 22.5) {
		this->stepDirection = 2;
	}
	else if (angle < 22.5 && angle > -22.5) {
		this->stepDirection = 3;
	}
	else if (angle <= -22.5 && angle >= -67.5) {
		this->stepDirection = 4;
	}
	else if (angle < -67.5 && angle > -112.5) {
		this->stepDirection = 5;
	}
	else if (angle <= -112.5 && angle >= -157.5) {
		this->stepDirection = 6;
	}
	else if (angle < -157.5 || angle > 157.5) {
		this->stepDirection = 7;
	}
	else if (angle <= 157.5 && angle >= 112.5) {
		this->stepDirection = 8;
	}
	else {
		this->stepDirection = 0;
	}
	std::cout << "this->stepDirection: " << this->stepDirection << std::endl;
}


void Enemy::moveAwayFromObstacles()
{
}

void Enemy::renderEnemy(sf::RenderTarget& target)
{
	target.draw(this->enemySprite);
}

void Enemy::EnemyUpdate(World world, Player player, float dt, float dtFRIM)
{
	this->step(world, player, dtFRIM);
	anims[int(this->currentAnim)].update(dt);
	anims[int(this->currentAnim)].setToSprite(this->enemySprite);
}

EnemyAnimation::EnemyAnimation(int x, int y, int w, int h, std::string textureLink)
{
	if (!this->texture.loadFromFile(textureLink)) {
		std::cout << "Failed load: Enemy Animation Texture" << std::endl;
		system("pause");
	};
	for (int i = 0; i < this->numFrames; i++) {
		frames[i] = { x + i * w, y, w, h };
	}
}

void EnemyAnimation::setToSprite(sf::Sprite& s) const
{
	s.setTexture(this->texture);
	s.setTextureRect(this->frames[this->frameIndex]);
}

void EnemyAnimation::update(float dt)
{
	this->time += dt;
	while (time >= animDelay) {
		time -= animDelay;
		this->advance();
	}
}

void EnemyAnimation::advance()
{
	if (++frameIndex >= numFrames) {
		frameIndex = 0;
	}
}
