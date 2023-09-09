#include "WorldTile.h"

WorldTile::WorldTile(float pX, float pY, std::string texture, bool isPassable, bool isExit)
{
	this->initTileSprite(texture);
	this->pos = sf::Vector2f(pX, pY);
	this->tileSprite.setPosition(pos);
	this->isPassable = isPassable;
	this->isExit = isExit;
}

void WorldTile::initTileTexture(std::string tileTexture)
{
	if (!this->tileTexture.loadFromFile(tileTexture)) {
		std::cout << "Failed load: Player Texture" << std::endl;
		system("pause");
	};
}

void WorldTile::setTileTextureRect(int x, int y, int l, int w)
{
	this->tileTextureRect = sf::IntRect(x, y, l, w);
	this->tileSprite.setTextureRect(this->tileTextureRect);
}

void WorldTile::initTileSprite(std::string tileTexture)
{
	this->initTileTexture(tileTexture);
	//this->tileTexture.setSmooth(true);
	this->tileSprite.setTexture(this->tileTexture);
	this->setTileTextureRect(0,0,32,32);
	sf::Rect<float> size = this->tileSprite.getGlobalBounds();
	this->tileSprite.setOrigin(sf::Vector2f(size.width / 2, size.height / 2));
}

sf::Sprite WorldTile::getTileSprite()
{
	return this->tileSprite;
}

int WorldTile::getTileSize()
{
	return this->tileSize;
}

bool WorldTile::isTilePassable()
{
	return this->isPassable;
}
