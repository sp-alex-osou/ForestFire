#pragma once

#include "Include.h"

class Game;

class GameComponent
{
public:
	GameComponent(Game& game);
	virtual ~GameComponent() = 0;

	virtual void init();
	virtual void update(float elapsed);
	virtual void draw(float elapsed);
protected:
	Game& game;
	CL_DisplayWindow& window;
};

