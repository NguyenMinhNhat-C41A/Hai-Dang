#pragma once
#include "SFML/Network.hpp"//Game Engine Classs
#include "SFML/Graphics.hpp"
#include "World.h"
#include "Window.h"

class Animation {
	public:
		Animation(int x, int y, int w, int h, std::string textureLink);
	private:
		static constexpr int NumFrames = 4;
		static constexpr float animDelay = 0.5f;
		sf::Texture texture;
		sf::IntRect frames[NumFrames];
		int frameIndex = 0;
		float time = 0.0f;
};
class Player {
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	sf::IntRect playerTextureRect;
	float gridPosX;
	float gridPosY;
	float stepSize;
	bool isPosAdjusted;
	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;
	sf::Clock clock;
	void initPlayerTexture(std::string textureLink);
	void setPlayerTextureRect(int x, int y, int l, int w);
	void initPlayerSprite(float pX, float pY);
	
public:
	Player(float pX, float pY);
	sf::Vector2f getPlayerGridPosition();
	void step(World world);
	void stepUp(World world);
	void stepDown(World world);
	void stepLeft(World world);
	void stepRight(World world);
	void adjustPos(World world);
	void animIdle();
	void animRun();

	void renderPlayer(sf::RenderTarget& target);
	void playerUpdate(World world);
};
