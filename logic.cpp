#include "logic.h"

logic::logic()
{
	_grid = new grid();
	graph = new Graphics(_grid);
}
logic::~logic()
{
	delete graph;
	delete _grid;

}
void logic::run()
{
	while (is_running)
	{
		handle_event();
		handle_logic();
		handle_graphics();
		SDL_Delay(100);
	}
}


void logic::handle_event()
{
	click = { -1,-1 };
	while (SDL_PollEvent(&_event) > 0)
	{
		switch (_event.type)
		{
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (_event.button.button)
			{
			case SDL_BUTTON_LEFT:
				click = { _event.motion.x, _event.motion.y };
				break;
			}
		}
	}
}

void logic::handle_logic()
{
	if (click.x != -1)
	{
		//process mouse click
		v2di grid_click = {(int)(GRID_SIZE * (float)click.x / (graph->wx)) , (int)(GRID_SIZE * (float)click.y / (graph->wy)) };
		std::cout << "New click, position = (" << grid_click.x << "," << grid_click.y << ") \n";
		v2di p1 = { grid_click.x - 1 , grid_click.y - 1 };
		v2di p2 = { grid_click.x + 1 , grid_click.y - 1 };
		graph->set_highlight({ p1,p2 });

	}
}

void logic::handle_graphics()
{
	graph->draw();
}
