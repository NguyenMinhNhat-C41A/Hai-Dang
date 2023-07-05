#pragma once
#include <iostream>
#include <chrono> 
#include "Window.h"
#include "Player.h"
#include "World.h"
class Game
{
private:
	Window* window;
	Player* player;
	World* world;
public:

	Game();

	virtual ~Game();

	void run();

	void update();

	void render();
};