#pragma once

#include "Graphics.h"
#include "vector2d.h"

class logic
{
public:
	void run();
	logic();
	~logic();
private:
	void handle_event();
	void handle_logic();
	void handle_graphics();
	SDL_Event _event;
	Graphics* graph = nullptr;
	grid* _grid = nullptr;
	bool is_running = true;

	v2di click = { 0,0 };

};

