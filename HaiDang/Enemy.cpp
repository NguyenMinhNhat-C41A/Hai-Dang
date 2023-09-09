#include "Enemy.h"

void Enemy::initEnemyTexture(std::string textureLink)
{
	if (!this->enemyTexture.loadFromFile(textureLink)) {
		std::cout << "Failed load: Player Texture" << std::endl;
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

	anims[int(AnimIndex::Idle)] = EnemyAnimation(0, 0, l, w, textureLink);
	anims[int(AnimIndex::Up)] = EnemyAnimation(0, 0 + w, l, w, textureLink);
	anims[int(AnimIndex::Left)] = EnemyAnimation(0, 0 + w * 2, l, w, textureLink);
	anims[int(AnimIndex::Down)] = EnemyAnimation(0, 0 + w * 3, l, w, textureLink);
	anims[int(AnimIndex::Right)] = EnemyAnimation(0, 0 + w * 4, l, w, textureLink);
	this->currentAnim = AnimIndex::Idle;
}

sf::Vector2f Enemy::getEnemyGridPosition()
{
	return sf::Vector2f(this->gridPosX, this->gridPosY);
}

void Enemy::step(World world, float dtFRIM)
{
}

void Enemy::stepUp(World world, float dtFRIM)
{
}

void Enemy::stepDown(World world, float dtFRIM)
{
}

void Enemy::stepLeft(World world, float dtFRIM)
{
}

void Enemy::stepRight(World world, float dtFRIM)
{
}

void Enemy::renderEnemy(sf::RenderTarget& target)
{
}

void Enemy::EnemyUpdate(World world, float dt, float dtFRIM)
{
	this->step(world, dtFRIM);
	anims[int(this->currentAnim)].update(dt);
	anims[int(this->currentAnim)].setToSprite(this->enemySprite);
}

EnemyAnimation::EnemyAnimation(int x, int y, int w, int h, std::string textureLink)
{
}

void EnemyAnimation::setToSprite(sf::Sprite& s) const
{
}

void EnemyAnimation::update(float dt)
{
}

void EnemyAnimation::advance()
{
	if (++frameIndex >= numFrames) {
		frameIndex = 0;
	}
}
