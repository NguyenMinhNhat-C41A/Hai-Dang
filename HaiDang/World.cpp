#include "World.h"

void World::initState()
{
	exitPos = sf::Vector2i(1,0);
	this->initEnemyPositions();
	this->initTiles();
}

void World::initEnemyPositions()
{
	this->enemyPositions.clear();
	this->enemyPositions.push_back(sf::Vector2i(0, 2));
	this->enemyPositions.push_back(sf::Vector2i(0, 6));
	this->enemyPositions.push_back(sf::Vector2i(2, 7));


}

void World::initTiles()
{
	this->tiles.clear();
	int posY = 0;
	for (int i = 1; i <= 30; i++) {
		int posX = 0;
		std::vector<WorldTile*> row;
		for (int j = 1; j <= 50; j++) {
			if (i == 1 || i == 30) {
				row.push_back(new WorldTile(posX, posY, "../img/OTheGioi/Tuong.png", false, false));
			}
			else {
				if (j == 1 || j == 50) {
					row.push_back(new WorldTile(posX, posY, "../img/OTheGioi/Tuong.png", false, false));
				}
				else {
					if(i >= 4 && i <= 20 && j >=4 && j <= 20) {
						row.push_back(new WorldTile(posX, posY, "../img/OTheGioi/Nuoc.png", false, false));
					}
					else {
						row.push_back(new WorldTile(posX, posY, "../img/OTheGioi/Co.png", true, false));
					}
				}
			}
			posX += 32;
		}
		this->tiles.push_back(row);
		posY += 32;
	}
	//std::cout << this->tiles.size() << std::endl;

	for (int i = 0; i < this->tiles.size(); i++) {
		//std::cout << "i: " << i << std::endl;
		//std::cout << this->tiles.at(i).size() << std::endl;
		
	}
}

World::World()
{
	this->gridLength = 50;
	this->initState();
}

void World::renderWorld(sf::RenderTarget& target)
{
	for (int i = 0; i < this->tiles.size(); i++) {
		for (int j = 0; j < this->tiles[i].size(); j++) {
			target.draw(this->tiles[i][j]->getTileSprite());
		}
	}
}

WorldTile World::getTile(int x, int y)
{
	//std::cout << "getTile: x: " << x << ", y: " << y << std::endl;
	return *this->tiles.at(y).at(x);
}


