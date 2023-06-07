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

void WorldTile::initTileSprite(std::string tileTexture)
{
	this->initTileTexture(tileTexture);
	this->tileTexture.setSmooth(true);
	this->tileSprite.setTexture(this->tileTexture);
	tileSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

}

sf::Sprite WorldTile::getTileSprite()
{
	return this->tileSprite;
}

bool WorldTile::isTilePassable()
{
	return this->isPassable;
}
