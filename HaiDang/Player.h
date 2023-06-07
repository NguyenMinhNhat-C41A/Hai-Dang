#pragma once
#include "SFML/Network.hpp"//Game Engine Classs
#include "SFML/Graphics.hpp"
#include "World.h"
#include "Window.h"

class Player {
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	float gridPosX;
	float gridPosY;
	float stepSize;
	sf::Clock clock;
	void initPlayerTexture(std::string textureLink);
	void initPlayerSprite(float pX, float pY);
public:
	Player(float pX, float pY);
	sf::Vector2f getPlayerGridPosition();
	void step(World world);
	void stepUp(World world);
	void stepDown(World world);
	void stepLeft(World world);
	void stepRight(World world);


	void renderPlayer(sf::RenderTarget& target);
	void playerUpdate(World world);
};
