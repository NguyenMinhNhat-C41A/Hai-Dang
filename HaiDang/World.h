#pragma once
#include "SFML/Graphics.hpp"
#include "WorldTile.h"
#include <vector>

#ifndef  WORLD_H
#define  WORLD_H

class World {
private:
	std::vector<std::vector<WorldTile*>> tiles;
	sf::Vector2i exitPos;
	std::vector<sf::Vector2i> enemyPositions;
	const int tileSize = 32;
	int gridLength;
	
	void initState();
	void initEnemyPositions();
	void initTiles();
public:
	World();
	void renderWorld(sf::RenderTarget& target);
	WorldTile getTile(int x, int y);
};
#endif // ! WORLD_H
