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

	std::vector<v2di> get_available_moves(int x, int y);
	void play(v2di origin, v2di dest);


	std::array<v2di,2> click; //store last two clicks {last click , new click}

	bool evaluate_click = false;
	bool selected = false;
	bool turn_1 = true; // true if it is player 1 turn, false otherwise

};

