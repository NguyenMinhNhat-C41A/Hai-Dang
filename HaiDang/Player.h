#pragma once
#include "SFML/Network.hpp"//Game Engine Classs
#include "SFML/Graphics.hpp"
#include "World.h"
#include "Window.h"

class Animation {
	public:
		Animation() = default;
		Animation(int x, int y, int w, int h, std::string textureLink);
		void setToSprite(sf::Sprite& s) const;
		void update(float dt);
	private:
		static constexpr int numFrames = 4;
		static constexpr float animDelay = 0.1f;
		sf::Texture texture;
		sf::IntRect frames[numFrames];
		int frameIndex = 0;
		float time = 0.0f;

		void advance();
};
class Player {
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	sf::IntRect playerTextureRect;
	float gridPosX;
	float gridPosY;
	float stepSize;
	enum class AnimIndex {
		Idle,
		Up,
		Left,
		Down,
		Right,
		Count
	};
	Animation anims[int(AnimIndex::Count)];
	AnimIndex currentAnim;
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


	void renderPlayer(sf::RenderTarget& target);
	void playerUpdate(World world, float dt);
};
