#pragma once

#include "Include.h"
#include "GameComponent.h"

#include <list>

class Game
{
public:
	Game(CL_DisplayWindow& display_window);
	void run();

	CL_DisplayWindow& getDisplayWindow() const;
private:
	void init();
	void draw();
	void update();

	void onKeyDown(const CL_InputEvent &key, const CL_InputState &state);
	void onWindowClose();

	float getElapsedTime() const;

	CL_DisplayWindow& window;

	bool quit;
	bool pause;

	CL_Slot slotQuit;
	CL_Slot slotKeyDown;

	std::list<GameComponent*> components;
};

