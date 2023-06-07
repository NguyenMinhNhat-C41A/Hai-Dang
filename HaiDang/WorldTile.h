#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#ifndef WORLDTILE_H
#define WORLDTILE_H

class WorldTile {
private:
	sf::Vector2f pos;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;

	bool isPassable;
	bool isExit;
public:
	WorldTile(float pX, float pY, std::string tileTexture, bool isPassable, bool isExit);
	void initTileTexture(std::string tileTexture);
	void initTileSprite(std::string tileTexture);
	sf::Sprite getTileSprite();
	bool isTilePassable();
};
#endif