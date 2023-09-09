#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#ifndef WORLDTILE_H
#define WORLDTILE_H

class WorldTile {
private:
	sf::Vector2f pos;
	sf::Texture tileTexture;
	sf::IntRect tileTextureRect;
	sf::Sprite tileSprite;
	const int tileSize = 32;
	bool isPassable;
	bool isExit;
public:
	WorldTile(float pX, float pY, std::string tileTexture, bool isPassable, bool isExit);
	void initTileTexture(std::string tileTexture);
	void setTileTextureRect(int x, int y, int l, int w);
	void initTileSprite(std::string tileTexture);
	sf::Sprite getTileSprite();
	int getTileSize();
	bool isTilePassable();
};
#endif