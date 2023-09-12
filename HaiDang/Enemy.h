#pragma once
#pragma once
#include "SFML/Network.hpp"//Game Engine Classs
#include "SFML/Graphics.hpp"
#include <cmath>

#include "Player.h"
#include "World.h"
#include "Window.h"

class EnemyAnimation {
public:
	EnemyAnimation() = default;
	EnemyAnimation(int x, int y, int w, int h, std::string textureLink);
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

class Enemy {
private:
	sf::Sprite enemySprite;
	sf::Texture enemyTexture;
	sf::IntRect enemyTextureRect;

	float gridPosX;
	float gridPosY;
	
	float stepSize;
	int stepMultiplayer;
	int stepDirection;
	int stepNums;

	enum class AnimIndex {
		Idle,
		Up,
		Left,
		Down,
		Right,
		Count
	};

	EnemyAnimation anims[int(AnimIndex::Count)];
	AnimIndex currentAnim;

	void initEnemyTexture(std::string textureLink);
	void setEnemyTextureRect(int x, int y, int l, int w);
	void initEnemySprite(float pX, float pY, int l, int w);
	
	void step(World world, Player player, float dtFRIM);
	void stepUp(World world, Player player, float dtFRIM);
	void stepDown(World world, Player player, float dtFRIM);
	void stepLeft(World world, Player player, float dtFRIM);
	void stepRight(World world, Player player, float dtFRIM);
	void stepNumsReset();

	void findPathToPlayer(Player player);
	void moveAwayFromObstacles();

public:
	Enemy(float pX, float pY, int l, int w, std::string textureLink);
	sf::Vector2f getEnemyGridPosition();

	void renderEnemy(sf::RenderTarget& target);
	void EnemyUpdate(World world, Player player, float dt, float dtFRIM);
};
